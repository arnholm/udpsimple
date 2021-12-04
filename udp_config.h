#ifndef UDP_CONFIG_H
#define UDP_CONFIG_H

#ifdef _MSC_VER

   #ifndef _WIN32_WINNT
      // this define is required by boost::asio on windows.
      #define _WIN32_WINNT 0x0601
   #endif

#endif // _MSC_VER
#endif // UDP_CONFIG_H
