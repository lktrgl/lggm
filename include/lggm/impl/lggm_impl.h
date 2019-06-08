#pragma once

#include <cstdint>
#include <ostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <type_traits>

namespace lggm
{

std::string const g_outFileName = "/home/boil/Work/MyTmp/lggm.txt";

enum class format : uint8_t
{
  none,
  timestamp = 0b1,
  file = 0b10,
  function = 0b100,
  line = 0b1000,
};

constexpr uint8_t g_defaultFormat = static_cast<std::underlying_type<format>::type> ( format::timestamp )
                                    | static_cast<std::underlying_type<format>::type> ( format::function )
                                    | static_cast<std::underlying_type<format>::type> ( format::line );
namespace details
{
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
} // namespace details

template <typename Stream>
class lggm
{
public:
  lggm ( Stream& stream ) : m_ofs ( stream )
  {
    if ( !details::streamTraits_t<Stream>::initStream ( m_ofs, m_outFileName, std::ios::out | std::ios::app ) )
    {
      throw std::runtime_error ( "cannot init the log stream" );
    }
  }

  void doMessage ( size_t lineNo, std::string const& functName, std::string const& msg )
  {
    if ( !details::streamTraits_t<Stream>::isStreamReady ( m_ofs ) )
    {
      return;
    }

    m_ofs << printTimestamp() << printDisposition ( lineNo, functName ) << msg << std::endl;
  }

  template <typename T>
  void doNameValue ( size_t lineNo, std::string const& functName, std::string const& name, T value )
  {
    if ( !details::streamTraits_t<Stream>::isStreamReady ( m_ofs ) )
    {
      return;
    }

    m_ofs << printTimestamp() << printDisposition ( lineNo,
          functName ) << "\"" << name << "\" = '"  << value  << "'" << std::endl;
  }

  void doScope ( size_t lineNo, std::string const& functName )
  {
    m_lineNo = lineNo;
    m_functName = functName;

    if ( !details::streamTraits_t<Stream>::isStreamReady ( m_ofs ) )
    {
      return;
    }

    outputScopedMessage ( "->" );
  }

  std::ostream& doStream ( size_t lineNo, std::string const& functName )
  {
    m_isStreamed = true;

    m_ofs << printTimestamp() << printDisposition ( lineNo, functName );

    return getOutStream();
  }

  ~lggm()
  {
    if ( !details::streamTraits_t<Stream>::isStreamReady ( m_ofs ) )
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
    }
  }

  static std::string const& getOutFileName()
  {
    return m_outFileName;
  }

  std::ostream& getOutStream()
  {
    return m_ofs;
  }

private:
  std::string printTimestamp()
  {
    if ( ! ( m_format & static_cast<std::underlying_type<format>::type> ( format::timestamp ) ) )
    {
      return {};
    }

    auto const start = std::chrono::system_clock::now();
    auto const in_time_t = std::chrono::system_clock::to_time_t ( start );

    std::stringstream ss;
    ss << std::put_time ( std::localtime ( &in_time_t ), "%Y-%m-%d %H:%M:%S " );
    return ss.str();
  }

  std::string printDisposition ( size_t lineNo, std::string const& functName )
  {
    if ( ! ( m_format & ( static_cast<std::underlying_type<format>::type> ( format::function )
                          | static_cast<std::underlying_type<format>::type> ( format::line ) ) ) )
    {
      return {};
    }

    std::stringstream ss;

    if ( m_format & static_cast<std::underlying_type<format>::type> ( format::function ) )
    {
      ss << functName;
    }

    if ( m_format & static_cast<std::underlying_type<format>::type> ( format::line ) )
    {
      ss << ":" << lineNo << " ";
    }

    return ss.str();
  }

  void outputScopedMessage ( std::string const& msg )
  {
    m_isScoped = true;
    m_ofs << printTimestamp() << printDisposition ( m_lineNo, m_functName ) << msg << std::endl;
  }

private:
  bool m_isScoped = false;
  bool m_isStreamed = false;
  Stream& m_ofs;
  size_t m_lineNo{};
  std::string m_functName{};
  static constexpr uint8_t m_format = g_defaultFormat;
  static constexpr std::string const& m_outFileName = g_outFileName;
};

} // namespace lggm
