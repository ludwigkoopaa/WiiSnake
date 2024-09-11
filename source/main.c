#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
//#include <grrlib.h>
#include <unistd.h>

static u32 *xfb;
static GXRModeObj *rmode;


void Initialise() {

  
	VIDEO_Init();
	WPAD_Init();
 
	rmode = VIDEO_GetPreferredMode(NULL);

	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
 
	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
}



  
int i, j, height = 20, width = 20;
int gameover, score;
int x, y, fruitx, fruity, flag;
  
// Generate the fruit

void setup()
{
    gameover = 0;
  
    // Height and width
    x = height / 2;
    y = width / 2;
label1:
    fruitx = rand() % 20;
    if (fruitx == 0)
        goto label1;
label2:
    fruity = rand() % 20;
    if (fruity == 0)
        goto label2;
    score = 0;
}
  
// Borders
void draw()
{
    //printf("\e[1;1H\e[2J");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (i == 0 || i == width - 1
                || j == 0
                || j == height - 1) {
                printf("#");
            }
            else {
                if (i == x && j == y)
                    printf("0");
                else if (i == fruitx
                         && j == fruity)
                    printf("*");
                else
                    printf(" ");
            }
        }
        printf("\n");
    }
  
    // Print Score at end
    printf("puan = %d", score);
    printf("\n");
    printf("Cikmak icin a ya basin");
}
  
// Input
void input()
{
	WPAD_ScanPads();
		
	u16 buttonsDown = WPAD_ButtonsDown(0);
	u16 buttonsHeld = WPAD_ButtonsHeld(0);
		if( buttonsDown & WPAD_BUTTON_UP ) {
			flag = 1;
			switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }
		}if( buttonsDown & WPAD_BUTTON_DOWN ) {
			flag = 3;
			switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }
		}if( buttonsDown & WPAD_BUTTON_LEFT ) {
			flag = 2;
			switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }
		}if( buttonsDown & WPAD_BUTTON_RIGHT ) {
			flag = 4;
			switch (flag) {
    case 1:
        y--;
        break;
    case 2:
        x++;
        break;
    case 3:
        y++;
        break;
    case 4:
        x--;
        break;
    default:
        break;
    }
		}if( buttonsDown & WPAD_BUTTON_A ) {
			gameover = 1;
		}			
        		
        
            
        

        
    
}
  

void logic()
{
    
    
  
    // Game over
    if (x < 0 || x > height
        || y < 0 || y > width)
        gameover = 1;
  
    // Update score
    if (x == fruitx && y == fruity) {
    label3:
        fruitx = rand() % 10;
        if (fruitx == 0)
            goto label3;
  
    // Generate new fruit
    label4:
        fruity = rand() % 10;
        if (fruity == 0)
            goto label4;
        score += 1;
    }
}
  


int main() {
 
	Initialise();
 
	printf("LUDWIG KOOPAA \n WiiSnake v1.0\n");
	/*while(1) {

		WPAD_ScanPads();
		
		u16 buttonsDown = WPAD_ButtonsDown(0);
		u16 buttonsHeld = WPAD_ButtonsHeld(0);
		
		if( buttonsDown & WPAD_BUTTON_A ) {
			printf("a\n");
		}	
		
		if( buttonsHeld & WPAD_BUTTON_A ) {
			printf("A\n");
		}	}*/
	int m, n;
  

    setup();
  

    while (!gameover) {
  

        draw();
        input();
        logic();
    }
	
	return 0;
}
