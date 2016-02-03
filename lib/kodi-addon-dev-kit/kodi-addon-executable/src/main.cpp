/*
 *      Copyright (C) 2015 Team KODI
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with KODI; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "kodi/addon.api2/AddonLib.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <p8-platform/util/timeutils.h>
#include <p8-platform/threads/threads.h>

using namespace P8PLATFORM;


class CThreadTest : public P8PLATFORM::CThread
{
public:
  CThreadTest();
  ~CThreadTest();

protected:
  virtual void *Process(void);

private:
  KODI_HANDLE m_aHandle;
};

CThreadTest::CThreadTest()
 : m_aHandle(NULL)
{
  CreateThread();
}

CThreadTest::~CThreadTest()
{
}

void* CThreadTest::Process(void)
{
  m_aHandle = KodiAPI_InitThread();

  int cnt = 8;
  while (!IsStopped())
  {
    //sleep(1);
    cnt--;
    KodiAPI_Log(m_aHandle, LOG_ERROR, "Countdown               ---> %i", cnt);
    
    if (cnt == 0)
      break;
  }
  
  KodiAPI_Finalize(m_aHandle);
  return NULL;
}






KODI_HANDLE aHandle;

int frequency_of_primes (int n) {
  int i,j;
  int freq=n-1;
  uint64_t count = 0;
  for (i=2; i<=n; ++i)
  {
    for (j=sqrt(i);j>1;--j)
    {
      if (i%j==0) 
      {
        --freq; 
        break;
      }
        ++count;
    }
  }
  fprintf(stderr, "count = %lu\n", count);
  return freq;
}

/**
 * Currently for test purpose is library a executable.
 */
int main(int argc, char *argv[])
{
  addon_properties props;
  props.addon_name      = "Demo binary add-on";
  props.is_independent  = false;
  props.use_net_only    = false;

  //sleep(5);
  
  aHandle = KodiAPI_Init(argc, argv, &props);
  if (aHandle == NULL)
  {
    fprintf(stderr, "Binary AddOn: %i %s\n", KODI_API_lasterror, KodiAPI_ErrorCodeToString(KODI_API_lasterror));
    return 1;
  }
  
  KodiAPI_Log(aHandle, LOG_ERROR, "Hello, World from Log");
  
  sleep(4);
   //CThreadTest test;
  
  CThreadTest* test2 = new CThreadTest;
  CThreadTest* test3 = new CThreadTest;
  CThreadTest* test4 = new CThreadTest;
  CThreadTest* test5 = new CThreadTest;
//   CThreadTest* test6 = new CThreadTest;
//   CThreadTest* test7 = new CThreadTest;
//   CThreadTest* test8 = new CThreadTest;
//   CThreadTest* test9 = new CThreadTest;
//   CThreadTest* test10 = new CThreadTest;
//   CThreadTest* test11 = new CThreadTest;
//   CThreadTest* test12 = new CThreadTest;
//   CThreadTest* test13 = new CThreadTest;
  sleep(10);
  delete test2;
  delete test3;
  delete test4;
  delete test5;
  
  
  
  
/*
  clock_t t;
  int f;
  t = clock();
  printf ("Calculating...\n");
  f = frequency_of_primes (99999);
  printf ("The number of primes lower than 100,000 is: %d\n",f);
  t = clock() - t;
  printf ("It took me %ld clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
  */

//sleep(10);

KodiAPI_Log(aHandle, LOG_ERROR, "He22llo, World from Log");

  KodiAPI_Finalize(aHandle);

  return 0;
}
