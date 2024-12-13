#include "comand.h"
//#include <Ps3Controller.h>

void CNTR_PUTS(void){
  static int syaga=0,motion_mode=0,first=0,mode=0,LED_mode=0x01,flont=0,gur=0,stnd=0,tiny=0,zengo=0,demo_mode=0;
	switch (CONTLLOR()*motion_mode){
        case 0:
            //PS4.sendToController();
            if(CONTLLOR()==C_P_LEF){
                LED_mode=0x02;
                player=2;
                PS4.setLed(10*PS4.Battery(), 0, 0);
            }
            if(CONTLLOR()==C_P_RIG){
                LED_mode=0x01;
                player=1;
                PS4.setLed(0, 0, 10*PS4.Battery());
            }
            if(CONTLLOR()==C_START){
                motion_mode=1;
            }
            if(CONTLLOR()==C_L2){
                player=3;
                PS4.setLed(0, 10*PS4.Battery(), 0);
                zerro_ALL();
            }else{
                toruqe_off();
            }
            LEDOUT(LED_mode);
        break;

        case C_START:
            switch(mode){
              case 0:
                rightarm(0,40,90,50,0);
                leftarm(0,40,90,50,0);
              break;

               case 1:
                rightarm(0,30,0,50,0);
                leftarm(0,30,0,50,0);
              break;
            }
            switch(tiny){
              case 0:
                rightleg(15,35, -45, -20);
	              leftleg(15,35, -45, -20);
              break;

              case 1:
                rightleg(5,35, -45, -10);
                leftleg(5,35, -45, -10);
              break;
            }
	              kosi(0);

                rightarm_strech(100,90,60,90,90);
                leftarm_strech(100,90,60,90,90);
                rightleg_strech(100,90,100,90);
                leftleg_strech(100,90,100,90);
                kosi_strech(60);

                rightarm_speed(127,127,127,127,127);
                leftarm_speed(127,127,127,127,127);
                rightleg_speed(127,127,127,127);
                leftleg_speed(127,127,127,127);
                kosi_speed(127);
        break;
        
        case C_START & C_RIGHT:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            side_work_R(mode);
        break;

        case C_START & C_LEFT:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            side_work_L(mode);
        break;

        case C_UP:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            suri_flont(mode,tiny);
            flont=1;
        break;
        
        case C_UP & C_START:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            wolk_flont(mode);
            flont=1;
        break;

        case C_DOWN & C_START:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            wolk_back(mode);
            flont=1;
        break;

        case C_DOWN:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            suri_back(mode,tiny);
            flont=2;
        break;
        
        case C_RIGHT:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            side_R(mode,tiny);
        break;

        case C_RIGHT & C_R1:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            side_roll_R(mode);
        break;
        
        case C_LEFT:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            side_L(mode);
        break;

        case C_LEFT & C_L1:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            side_roll_L(mode);
        break;
        
        case C_CR:
            if(first==0){
                first=1;
                cnt_time=0;
            }
           harai_R(tiny);
        break;

        case C_CR & C_UP:
            if(first==0){
                first=1;
                cnt_time=0;
            }
           under_R(tiny);
        break;

        case C_SQ & C_UP:
            if(first==0){
                first=1;
                cnt_time=0;
            }
           under_L(tiny);
        break;
        
        case C_TR:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            gur=1;
            if(stnd==0){
              gurd(mode);
            }else{
              syagami(mode,tiny);
            }
        break;
        
        case C_SQ:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            harai_L(tiny);
        break;
        
        case C_PEC:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            if(j_flag==1){
              if(pitch_feed<60 && pitch_feed>20 && zengo==0){
                zengo=1;
                cnt_time=500;
              }
              if(pitch_feed>60){
                zengo=3;
              }
            }else{
              zengo=0;
            }
            if(demo_mode!=1){
              syagami(mode,zengo);
            }
            syaga=1;
        break;

        case C_PEC & C_DOWN:
            if(first==0 || syaga==1){
                first=1;
                cnt_time=0;
                syaga=0;
            }
            stand_back(mode);
        break;
        
        case C_TR & C_DOWN:
            if(first==0 || gur==1){
                first=1;
                cnt_time=0;
                gur=0;
            }
            stand_back(2);
            stnd=1;
        break;

        case C_PEC & C_RIGHT:
            if(first==0 || syaga==1){
                first=1;
                cnt_time=0;
                syaga=0;
            }
            stand_side_R();
        break;

        case C_PEC & C_LEFT:
            if(first==0 || syaga==1){
                first=1;
                cnt_time=0;
                syaga=0;
            }
            stand_side_L();
        break;

        case C_PEC & C_UP:
            if(first==0 || syaga==1){
                first=1;
                cnt_time=0;
                syaga=0;
            }
            stand_flont(mode);
        break;
        
        case C_TR & C_UP:
            if(first==0 || gur==1){
                first=1;
                cnt_time=0;
                gur=0;
            }
            stand_flont(2);
            stnd=1;
        break;

        case C_L1:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            roll_L(mode,tiny);
        break;

        case C_R1:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            roll_R(mode,tiny);
        break;

        case C_R1 & C_L1:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            if(demo_mode!=1){
              zenten(tiny);
            }
        break;

        case C_START & C_SQ:
        if(first==0){
                first=1;
                cnt_time=0;
            }
            back_drop();
        break;
        
        case C_R2:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            if(demo_mode!=1){
              fuck_R_high(); 
            }else{
              catch_R(tiny);
            }
        break;

        case C_L2:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            if(demo_mode!=1){
              fuck_L_high();
            }else{
              catch_L(tiny);
            }
        break;
        
        case C_L2 & C_UP:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            humikomi_L(mode);
        break;

        case C_L1 & C_UP:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            small_humikomi_L(mode);
        break;

        case C_R2 & C_UP:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            humikomi_R(mode);
        break;
        

        case C_R2 & C_DOWN:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            if(demo_mode!=1){
              fuck_R_low();
            }
        break;

        case C_L2 & C_DOWN:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            if(demo_mode!=1){
              fuck_L_low();
            }
        break;

        case C_L2 & C_LEFT:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            if(demo_mode!=1){
              fuck_L_low();
            }
        break;

        case C_L2 & C_RIGHT:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            if(demo_mode!=1){
              fuck_L_low();
            }
        break;

        case C_R2 & C_RIGHT:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            if(demo_mode!=1){
              fuck_R_low();
            }
        break;

        case C_R2 & C_LEFT:
            if(first==0){
                first=1;
                cnt_time=0;
            }
            if(demo_mode!=1){
              fuck_L_low();
            }
        break;

        case C_P_LEF:
            if(first==0){
              first=1;
              cnt_time=0;
              if(mode==0){
                mode=1;
                rightarm_strech(60,90,120,90,90);
	              leftarm_strech(60,90,120,90,90);
                rightarm(0,30,0,30,0);
			          leftarm(0,30,0,30,0);
              }else{
                mode=0;
                rightarm_strech(60,90,120,90,90);
	              leftarm_strech(60,90,120,90,90);
                rightarm(0,0,90,30,0);
			          leftarm(0,0,90,30,0);
              }
            }
        break;

        case C_P_RIG:
            if(first==0){
                first=1;
                cnt_time=0;
                if(tiny==0){
                  tiny=0;//2
                }else{
                  tiny=0;
                }
            }
        break;
        
        case C_L2 & C_R2 & C_LEFT:
          if(first==0){
                first=1;
                cnt_time=0;
            }
          side_kick_L();
        break;
        
        case C_L2 & C_R2 & C_RIGHT:
          if(first==0){
                first=1;
                cnt_time=0;
            }
          side_kick_R();
        break;
        
        case C_SEL:
            motion_mode=0;
        break;

        case C_DEF:
            if(first>0){
                cnt_time=0;
                first=0;
                kosi(0);
            }
            if(flont==2 & tiny==0){
              if(mode==0){
                rightarm(0,-20,90,360,35);
                leftarm(0,-20,90,360,35);
              }else{
                rightarm(0,70,0,360,25);
                leftarm(0,70,0,360,25);
              }
              rightleg(15,30, -45, -20);
	            leftleg(15,30, -45, -20);
	            kosi(0);
                if(cnt_time>1500){
                    flont=0;
                }
			    }else if(flont==1 & tiny==0){
              if(mode==0){
                rightarm(0,0,90,360,-15);
                leftarm(0,0,90,360,-15);
              }else{
                rightarm(0,0,0,360,-15);
                leftarm(0,0,0,360,-15);
              }
              rightleg(15,40, -40, -20);
	            leftleg(15,40, -40, -20);
	            kosi(0);
                if(cnt_time>1000){
                    flont=0;
                }
			    }else if(gur==1){
              rightleg(15,35, -45, -60);
	            leftleg(15,35, -45, -60);
	            kosi(0);
                if(cnt_time>1000){
                    gur=0;
                }      
            }else{
              LEDOUT(LED_mode);
              bace(mode,tiny);
            }
            stnd=0;
            zengo=0;
        break;
    }	

    if(CONTLLOR()!=C_DEF){
      flont=0;
    }
}