#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

namespace lggm
{

std::string const g_outFileName = "/home/boil/Work/MyTmp/lggm.txt";

enum /*class*/ format : uint8_t
{
  none,
  timestamp = 0b1,
  file = 0b10,
  function = 0b100,
  line = 0b1000,
};

constexpr uint8_t g_defaultFormat = format::timestamp | format::function | format::line;

class lggm
{
public:
  lggm ( size_t lineNo, std::string const& functName, std::string const& msg )
    : m_ofs ( m_outFileName, std::ios::out | std::ios::app )
  {
    if ( !m_ofs.is_open() )
    {
      return;
    }

    m_ofs << printTimestamp() << printDisposition ( lineNo, functName ) << msg << std::endl;

  }

  template <typename T>
  lggm ( size_t lineNo, std::string const& functName, std::string const& valueName, T value )
    : m_ofs ( m_outFileName, std::ios::out | std::ios::app )
  {
    if ( !m_ofs.is_open() )
    {
      return;
    }

    m_ofs << printTimestamp() << printDisposition ( lineNo,
          functName ) << "\"" << valueName << "\" = '"  << value  << "'" << std::endl;

  }

  lggm ( size_t lineNo, std::string const& functName )
    : m_ofs ( m_outFileName, std::ios::out | std::ios::app )
    , m_lineNo ( lineNo )
    , m_functName ( functName )
  {
    if ( !m_ofs.is_open() )
    {
      return;
    }

    outputScopedMessage ( "->" );
  }

  ~lggm()
  {
    if ( !m_isScoped )
    {
      return;
    }

    if ( !m_ofs.is_open() )
    {
      return;
    }

    outputScopedMessage ( "<-" );
  }

private:
  std::string printTimestamp()
  {
    if ( ! ( m_format & format::timestamp ) )
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
    if ( ! ( m_format & ( format::function | format::line ) ) )
    {
      return {};
    }

    std::stringstream ss;

    if ( m_format & format::function )
    {
      ss << functName;
    }

    if ( m_format & format::line )
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
  std::ofstream m_ofs;
  size_t m_lineNo{};
  std::string m_functName{};
  static constexpr std::string const& m_outFileName = g_outFileName;
  static constexpr uint8_t m_format = g_defaultFormat;
};

} // namespace lggm

#define LGGM_CAT(a,b) LGGM_CAT2(a, b)
#define LGGM_CAT2(a,b) a ## b

#define LS() lggm::lggm LGGM_CAT(a,__LINE__) ( __LINE__, __PRETTY_FUNCTION__ )

#define LT() do { lggm::lggm LGGM_CAT(a,__LINE__)( __LINE__, __PRETTY_FUNCTION__ , "trace"); } while(0);

#define LM(m) do { lggm::lggm LGGM_CAT(a,__LINE__)( __LINE__, __PRETTY_FUNCTION__ , m ); } while(0);

#define L(v) do { lggm::lggm LGGM_CAT(a,__LINE__)( __LINE__, __PRETTY_FUNCTION__ , #v , v ); } while(0);


