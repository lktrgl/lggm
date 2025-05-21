#pragma once

/*---------------------------------------------------------------------------*/

#include <cstdint>
#include <ostream>
#include <fstream>
#include <string>
#include <string_view>
#include <chrono>
#include <iomanip>
#include <tuple>
#include <type_traits>

/*---------------------------------------------------------------------------*/

namespace lggm
{

/*---------------------------------------------------------------------------*/

std::string const g_outFileName = "/home/boil/Work/MyTmp/lggm.txt";

/*---------------------------------------------------------------------------*/

enum class format : uint8_t
{
  none,
  timestamp = 0b1,
  file = 0b10,
  function = 0b100,
  line = 0b1000,
};

/*---------------------------------------------------------------------------*/

constexpr uint8_t g_defaultFormat = static_cast<std::underlying_type<format>::type> ( format::timestamp )
                                    | static_cast<std::underlying_type<format>::type> ( format::function )
                                    | static_cast<std::underlying_type<format>::type> ( format::line );

/*---------------------------------------------------------------------------*/

constexpr size_t g_defaultRullerWidth = 20;

/*---------------------------------------------------------------------------*/

namespace details
{

/*---------------------------------------------------------------------------*/

// Note: this include has been placed here to make the version information falling under the 'details' namespace scope
#include <lggm/versions/version_info_lggm.h>

/*---------------------------------------------------------------------------*/

template <typename Stream>
struct streamTraits_t
{
  static bool initStream ( Stream& stream, ... )
  {
    static_assert ( std::is_base_of<std::ostream, Stream>::value, "use sort of stream for Stream type" );
    return stream.good();
  }

  static bool isStreamReady ( Stream& stream )
  {
    return stream.good();
  }
};

/*---------------------------------------------------------------------------*/

template <>
struct streamTraits_t<std::ofstream>
{
  static bool initStream ( std::ofstream& stream, std::string const& fileName, std::ios::openmode mode )
  {
    stream.open ( fileName, mode ) ;
    return stream.is_open() && stream.good();
  }

  static bool isStreamReady ( std::ofstream& stream )
  {
    return stream.is_open() && stream.good();
  }
};

/*---------------------------------------------------------------------------*/

template < typename CONTAINER >
class is_iterable
{
  template < typename U, typename = decltype (std::cbegin (std::declval<std::remove_cv_t<U >> () ) ) >
  static std::true_type test_cbegin (std::nullptr_t );
  template < typename U >
  static std::false_type test_cbegin ( ... );

  template < typename U, typename = decltype (std::cend (std::declval<std::remove_cv_t<U >> () ) ) >
  static std::true_type test_cend (std::nullptr_t );
  template < typename U >
  static std::false_type test_cend ( ... );

public:
  static constexpr bool value = decltype ( test_cbegin<CONTAINER> ( nullptr ) ) ::value
                                && decltype ( test_cend<CONTAINER> ( nullptr ) ) ::value;
};

/*---------------------------------------------------------------------------*/

template < typename CONTAINER >
constexpr bool is_iterable_v = is_iterable<CONTAINER>::value;

/*---------------------------------------------------------------------------*/

template < typename CONTAINER >
struct is_basic_string : std::false_type {};

/*---------------------------------------------------------------------------*/

template < template<typename, typename, typename> typename CONTAINER, typename SUBTYPE, typename TRAITS, typename ALLOCATOR>
class is_basic_string<CONTAINER<SUBTYPE, TRAITS, ALLOCATOR >>
{
  using type = std::remove_cv_t<CONTAINER<SUBTYPE, TRAITS, ALLOCATOR >>;

public:
  static constexpr bool value = std::is_same<std::basic_string<SUBTYPE, TRAITS, ALLOCATOR>, type> ::value;
};

/*---------------------------------------------------------------------------*/

template < typename CONTAINER >
constexpr bool is_basic_string_v = is_basic_string<CONTAINER>::value;

/*---------------------------------------------------------------------------*/

template < typename CONTAINER >
struct is_basic_string_view : std::false_type {};

/*---------------------------------------------------------------------------*/

template < template<typename, typename> typename CONTAINER, typename SUBTYPE, typename TRAITS>
class is_basic_string_view<CONTAINER<SUBTYPE, TRAITS >>
{
  using type = std::remove_cv_t<CONTAINER<SUBTYPE, TRAITS >>;

public:
  static constexpr bool value = std::is_same<std::basic_string_view<SUBTYPE, TRAITS>, type> ::value;
};

/*---------------------------------------------------------------------------*/

template < typename CONTAINER >
constexpr bool is_basic_string_view_v = is_basic_string_view<CONTAINER>::value;

/*---------------------------------------------------------------------------*/

} // namespace details

/*---------------------------------------------------------------------------*/

template <typename Stream>
class lggm
{
public:
  lggm ( Stream& stream, size_t lineNo, std::string const& functName )
    : m_outputStream ( stream )
    , m_lineNo ( lineNo )
    , m_functName ( functName )
  {
    if (! details::streamTraits_t<Stream>::initStream ( getOutStream(), m_outFileName, std::ios::out | std::ios::app ) )
    {
      throw std::runtime_error ( "cannot init the log stream" );
    }
  }

  void doMessage ( std::string const& msg )
  {
    if (! details::streamTraits_t<Stream>::isStreamReady ( getOutStream() ) )
    {
      return;
    }

    doStreamPrefix() << msg << std::endl;

    getOutStream().flush();
  }

  template <size_t PLACEHOLDER_COUNT, typename T>
  void doRuler ( T const& a, T const& b, std::string const& name, T const& value )
  {
    if (! details::streamTraits_t<Stream>::isStreamReady ( getOutStream() ) )
    {
      return;
    }

    if ( not isRulerPointValid<T> ( a, b, value ) )
    {
      return;
    }

    size_t const valuePosition = getRulerValuePosition<PLACEHOLDER_COUNT, T> ( a, b, value );

    doStreamPrefix()
        << name << ":";

    doRulerLineValue<PLACEHOLDER_COUNT, T> ( valuePosition );

    getOutStream()
        << ":[" << a << ", " << value << ", " << b << "]"
        << std::endl;

    getOutStream().flush();
  }

  template <size_t PLACEHOLDER_COUNT, typename T>
  void doPlaneRuler ( T const& a1, T const& b1, T const& a2, T const& b2,
                      std::string const& name1, T const& value1,
                      std::string const& name2, T const& value2 )
  {
    if (! details::streamTraits_t<Stream>::isStreamReady ( getOutStream() ) )
    {
      return;
    }

    if ( not isRulerPointValid<T> ( a1, b1, value1 )
         or
         not isRulerPointValid<T> ( a2, b2, value2 ) )
    {
      return;
    }

    size_t const valuePosition1 = getRulerValuePosition<PLACEHOLDER_COUNT, T> ( a1, b1, value1 );

    size_t const valuePosition2 = getRulerValuePosition<PLACEHOLDER_COUNT, T> ( a2, b2, value2 );


    for ( size_t i = 0U; i < valuePosition2; ++i )
    {
      doRulerLineNoValue<PLACEHOLDER_COUNT> ();
      getOutStream()
          << std::endl;
    }

    doRulerLineValue<PLACEHOLDER_COUNT, T> ( valuePosition1 );
    getOutStream()
        << std::endl;


    for ( size_t i = valuePosition2 + 1; i < PLACEHOLDER_COUNT; ++i )
    {
      doRulerLineNoValue<PLACEHOLDER_COUNT> ();
      getOutStream()
          << std::endl;
    }

    getOutStream()
        << "{ "
        << name1 << ":[" << a1 << ", " << value1 << ", " << b1 << "], "
        << name2 << ":[" << a2 << ", " << value2 << ", " << b2 << "] "
        << "}"
        << std::endl;

    getOutStream().flush();
  }

  template <typename T>
  void doVectorNameValue ( std::string const& name, T const& value )
  {
    if (! details::streamTraits_t<Stream>::isStreamReady ( getOutStream() ) )
    {
      return;
    }

    doStreamPrefix() << "\"" << name << "\" = " << value.size() << " : { ";

    bool isFirst = true;

    for ( auto it = std::cbegin ( value ); it not_eq std::cend ( value ); ++it )
    {
      getOutStream()
          << ( isFirst ? ( isFirst = false, "" ) : ", " )
          << *it;
    }

    getOutStream() << " }" << std::endl;

    getOutStream().flush();
  }

  template <typename ... ARGS>
  void doNameValue ( std::string const& name,
                     std::tuple<ARGS...> const& value )
  {
    doNameValue_tuple<ARGS...> ( name, value, std::make_integer_sequence<size_t, sizeof... (ARGS ) >() );
  }

#ifdef QSTRING_H
  template <typename T>
  std::enable_if_t<not std::is_enum<T>::value and std::is_same<QString, T>::value, void>
  doNameValue ( std::string const& name, T value )
  {
    if (! details::streamTraits_t<Stream>::isStreamReady ( getOutStream() ) )
    {
      return;
    }

    doStreamPrefix() << "\"" << name
                     << "\" = '"
                     << value.toStdString()
                     << "'" << std::endl;

    getOutStream().flush();
  }

  template <typename T>
  std::enable_if_t<not std::is_enum<T>::value and not std::is_same<QString, T>::value, void>
  doNameValue ( std::string const& name, T value )
  {
    if (! details::streamTraits_t<Stream>::isStreamReady ( getOutStream() ) )
    {
      return;
    }

    doStreamPrefix() << "\"" << name
                     << "\" = '"
                     << value
                     << "'" << std::endl;

    getOutStream().flush();
  }

#else
  template <typename T>
  std::enable_if_t<not std::is_enum<T>::value, void>
  doNameValue ( std::string const& name, T value )
  {
    if (! details::streamTraits_t<Stream>::isStreamReady ( getOutStream() ) )
    {
      return;
    }

    doStreamPrefix() << "\"" << name
                     << "\" = '"
                     << value
                     << "'" << std::endl;

    getOutStream().flush();
  }

#endif // ifdef QSTRING_H

  template <typename T>
  std::enable_if_t<std::is_enum<T>::value, void>
  doNameValue ( std::string const& name, T value )
  {
    if (! details::streamTraits_t<Stream>::isStreamReady ( getOutStream() ) )
    {
      return;
    }

    doStreamPrefix() << "\"" << name
                     << "\" = '"
                     << static_cast<size_t> ( static_cast<typename std::underlying_type<T>::type> ( value ) )
                     << "'" << std::endl;

    getOutStream().flush();
  }

  template <typename T>
  void doNameHexValue ( std::string const& name, T const* value, size_t value_len )
  {
    if (! details::streamTraits_t<Stream>::isStreamReady ( getOutStream() ) )
    {
      return;
    }

    doStreamPrefix() << "\"" << name
                     << "\" = " << value_len << " : { ";

    unsigned char const* p_begin = reinterpret_cast<unsigned char const*> ( value );
    unsigned char const* p_end = reinterpret_cast<unsigned char const*> ( value ) + value_len;

    bool is_first_item = true;

    for ( unsigned char const* p = p_begin; p < p_end; ++p )
    {
      if ( is_first_item )
      {
        is_first_item = false;
      }
      else
      {
        getOutStream() << ", ";
      }

      getOutStream() << "0x" << std::hex << std::setw ( 2 ) << std::setfill ( '0' ) << static_cast<int> (*p );
    }

    getOutStream() << " }" << std::endl;

    getOutStream().flush();
  }

  void doScope ()
  {
    if (! details::streamTraits_t<Stream>::isStreamReady ( getOutStream() ) )
    {
      return;
    }

    outputScopedMessage ( "->" );
  }

  ~lggm()
  {
    if (! details::streamTraits_t<Stream>::isStreamReady ( getOutStream() ) )
    {
      return;
    }

    if ( m_isScoped )
    {
      outputScopedMessage ( "<-" );
    }
    else if ( m_isStreamed )
    {
      getOutStream() << std::endl;

      getOutStream().flush();
    }
  }

  static std::string const& getOutFileName()
  {
    return m_outFileName;
  }

  static std::string_view getVersion()
  {
    return std::string_view (
             reinterpret_cast<const char*> ( lggm::details::gen::code_template::version_info_lggm_txt ),
             lggm::details::gen::code_template::version_info_lggm_txt_len
           );
  }

private:
  template <typename ... ARGS, size_t ... Indexes>
  void doNameValue_tuple ( std::string const& name,
                           std::tuple<ARGS...> const& value,
                           std::integer_sequence<size_t, Indexes...> )
  {
    if (! details::streamTraits_t<Stream>::isStreamReady ( getOutStream() ) )
    {
      return;
    }

    doStreamPrefix() << "\"" << name
                     << "\" = { ";

    bool isFirst = true;

    ( ( getOutStream()
        << ( isFirst ? ( isFirst = false, "" ) : "; " )
        << std::get<Indexes> ( value ) ), ... );
    getOutStream()  << " }" << std::endl;

    getOutStream().flush();
  }

  template <typename T>
  bool isRulerPointValid ( T const& a, T const& b, T const& value )
  {
    return not ( b == a or value > b or value < a );
  }

  template <size_t PLACEHOLDER_COUNT, typename T>
  size_t getRulerValuePosition ( T const& a, T const& b, T const& value )
  {
    return static_cast<double> ( value - a )
           / static_cast<double> ( b - a )
           * static_cast<double> ( PLACEHOLDER_COUNT );
  }

  template <size_t PLACEHOLDER_COUNT, typename T>
  void doRulerLineValue ( size_t valuePosition )
  {
    getOutStream()
        << "[";

    for ( size_t i = 0U; i < valuePosition; ++i )
    {
      getOutStream() << "-";
    }

    getOutStream() << "*";

    for ( size_t i = valuePosition + 1; i < PLACEHOLDER_COUNT; ++i )
    {
      getOutStream() << "-";
    }

    getOutStream()
        << "]";

    getOutStream().flush();
  }

  template <size_t PLACEHOLDER_COUNT>
  void doRulerLineNoValue ()
  {
    getOutStream()
        << "[";

    for ( size_t i = 0; i < PLACEHOLDER_COUNT; ++i )
    {
      getOutStream() << "-";
    }

    getOutStream()
        << "]";

    getOutStream().flush();
  }

  Stream& getOutStream()
  {
    return m_outputStream;
  }

  std::ostream& doStreamPrefix ( )
  {
    m_isStreamed = true;

    printTimestamp() << printDisposition ( m_lineNo, m_functName );

    return getOutStream();
  }

  Stream& printTimestamp()
  {
    if (! ( m_format & static_cast<std::underlying_type<format>::type> ( format::timestamp ) ) )
    {
      return getOutStream();
    }

    auto const start = std::chrono::system_clock::now();

#if defined(__GNUC__)
    auto const in_time_t = std::chrono::system_clock::to_time_t ( start );

    getOutStream() << std::put_time ( std::localtime (&in_time_t ), "%Y-%m-%d %H:%M:%S " );

    getOutStream().flush();
#elif defined(_MSC_VER)
    auto const tmm = std::chrono::system_clock::to_time_t ( start );

    struct tm mtm;
    localtime_s (&mtm, &tmm );

    // TODO: check formating string
    // this edition vs the next line's   m_outputStream << std::put_time ( &mtm, "%Y-%m-%d %X " );
    getOutStream() << std::put_time (&mtm, "%Y-%m-%d %H:%M:%S " );

    getOutStream().flush();
#else
#error undefined platform
#endif

    return getOutStream();
  }

  std::string printDisposition ( size_t lineNo, std::string const& functName )
  {
    if constexpr (! ( m_format & ( static_cast<std::underlying_type<format>::type> ( format::function )
                                   | static_cast<std::underlying_type<format>::type> ( format::line ) ) ) )
    {
      return {};
    }

    std::stringstream ss;

    if constexpr ( m_format & static_cast<std::underlying_type<format>::type> ( format::function ) )
    {
      ss << functName;
    }

    if constexpr ( m_format & static_cast<std::underlying_type<format>::type> ( format::line ) )
    {
      ss << ":" << lineNo << " ";
    }

    return ss.str();
  }

  void outputScopedMessage ( std::string const& msg )
  {
    m_isScoped = true;
    doStreamPrefix() << msg << std::endl;

    getOutStream().flush();
  }

private:
  bool m_isScoped = false;
  bool m_isStreamed = false;
  Stream& m_outputStream;
  size_t m_lineNo{};
  std::string m_functName{};
  static constexpr uint8_t m_format = g_defaultFormat;
  static constexpr std::string const& m_outFileName = g_outFileName;
};

/*---------------------------------------------------------------------------*/

} // namespace lggm
