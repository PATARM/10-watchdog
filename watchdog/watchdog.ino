/* @author: PAT (Pouria afshin tabar)
 * @Mail:   PAT.ARMarduino@gmail.com
 * @Github: PATARM
 * @brief:  Example WatchDog
 * @note :  IC is dependent on temperature and it has a low accuracy , if you have problems, you can email me
 */
 
#include <WatchDog.h>

int i = 3;
uint64_t t;
//_______________________________________________________________________________________________________________________________
void setup() {
  Serial3.begin(115200);
  delay(2000);
  Serial3.println();
  Serial3.println("------------------boot------------------");
  WDG.begin(1000);  //main 1000ms or t=1 second----so  after 1 second micro is going to Reset
}
//_______________________________________________________________________________________________________________________________
void loop() {
  if (i > 0) {
    WDG.reset();//watchdog counter will be ziro (Reset) --- we can write  WDG.refresh();  instead   WDG.reset();
    Serial3.println("Watchdog Refresh");
    t = millis();
    --i;
    delay(990);
  }
  else {
    Serial3.println(millis() - t);
    Serial3.flush();
  }
}
