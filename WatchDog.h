/* @author: PAT (Pouria afshin tabar)
 * @Mail:   PAT.ARMarduino@gmail.com
 * @Github: PATARM
 * @brief:  WatchDog
 */

#ifndef __WatchDog_H__
#define __WatchDog_H__
#include <libmaple/iwdg.h>
//_________________________________________________________________________________________________________________________________
class WatchDog {
  private:
    double x = 1;
    uint16_t n = 4, prescaler = IWDG_PR_DIV_4, reload = 10;
    //-----------------------------------------------------------------------------------
  public:
    void begin(uint32_t t) { //t -> ms
      x = t;
      x = (40 * x) / 4096;          //freq=40khz  time= (prescaler/40000)*reload  --- t(min)=(4/40000)*1=100us  ---  t(max)=(256/40000)*4096 = 26.2144 second
//      Serial3.print("x=");
//      Serial3.println(x);
      if (x <= 4) {
        prescaler = IWDG_PR_DIV_4;
        n = 4;
      }
      else if (x <= 8) {
        prescaler = IWDG_PR_DIV_8;
        n = 8;
      }
      else if (x <= 16) {
        prescaler = IWDG_PR_DIV_16;
        n = 16;
      }
      else if (x <= 32) {
        prescaler = IWDG_PR_DIV_32;
        n = 32;
      }
      else if (x <= 64) {
        prescaler = IWDG_PR_DIV_64;
        n = 64;
      }
      else if (x <= 128) {
        prescaler = IWDG_PR_DIV_128;
        n = 128;
      }
      else if (x <= 256) {
        prescaler = IWDG_PR_DIV_256;
        n = 256;
      }
      x = (40 * t) / n;
      reload = constrain(x, 1, 4096);
//      Serial3.print("reload =");
//      Serial3.println(reload);
//      Serial3.print("n =");
//      Serial3.println(n);
//      Serial3.flush();
      IWDG_BASE->KR = IWDG_KR_UNLOCK;     // Key register=UNLOCK
      IWDG_BASE->PR = prescaler;
      IWDG_BASE->RLR = reload;
      IWDG_BASE->KR = IWDG_KR_START;
      IWDG_BASE->KR = IWDG_KR_FEED;       //Refresh(Reset) WatchDog
    }
    //---------------------------------------------------------------------
    void refresh(void) {
      IWDG_BASE->KR = IWDG_KR_FEED;       //Refresh(Reset) WatchDog
    }
	 void reset(void) {
      IWDG_BASE->KR = IWDG_KR_FEED;       //Refresh(Reset) WatchDog
    }
};
#ifdef __cplusplus
extern "C" {
WatchDog WDG;
}
#endif
#endif
