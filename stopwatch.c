#include<reg52.h>
#define uchar unsigned char

sbit wela = P2^7;
sbit dula = P2^6;
uchar count = 0;
uchar numg = 0;
uchar nums = 0;
uchar numb = 0;
uchar numgfirst = 0;
uchar numsfirst = 0;
uchar code tablew[] = {0xfe,0xfd,0xfb};
uchar code tabled[] = {0x3f,0x06,0x5b,0x4f,
                       0x66,0x6d,0x7d,0x07,
                       0x7f,0x6f};

void timer1() interrupt 3{
	
	TH1 = (65536 - 10000)/256;
	TL1 = (65536 - 10000)%256;
	count++;
}

void init(){
	
	dula = 0;
	wela = 0;
	
	EA = 1;
	ET1 = 1;
	TMOD = 0x10;
	TR1 = 1;
	TH1 = (65536 - 10000)/256;
	TL1 = (65536 - 10000)%256;
}

void delay(uchar length){
	
	uchar x,y;
	for(x = length; x > 0; x--){
		
		for(y = 100; y > 0; y--){
			;
		}
	}
}

void display(uchar bai,uchar shi,uchar ge){
	
	dula = 1;
	P0 = bai;
	dula = 0;
	P0 = 0xff;
	wela = 1;
	P0 = tablew[0];
	wela = 0;
	delay(10);
	
	dula = 1;
	P0 = shi;
	dula = 0;
	P0 = 0xff;
	wela = 1;
	P0 = tablew[1];
	wela = 0;
	delay(10);
	
	dula = 1;
	P0 = ge;
	dula = 0;
	P0 = 0xff;
	wela = 1;
	P0 = tablew[2];
	wela = 0;
	delay(10);
}

void main(){
	
	init();
	display(tabled[0],tabled[0],tabled[0]);
	while(1){
		
		if(count == 1){
			
			count = 0;
			if(numsfirst){
				
				numb++;
				display(tabled[numb],tabled[nums],tabled[numg]);
				numsfirst = 0;
				if(numb == 10) {
				
					numb = 0;
					nums = 0;
					numg = 0;
					numsfirst = 0;
					numgfirst = 0;
				}
			}
			else if(numgfirst){
				
				nums++;
				display(tabled[numb],tabled[nums],tabled[numg]);
				numgfirst = 0;
				if(nums == 10) {
				
					nums = 0;
					numsfirst = 1;
				}
			}
			else{
				
				display(tabled[numb],tabled[nums],tabled[numg]);
				numg++;
				if(numg == 10) {
				
					numg = 0;
					numgfirst = 1;
				}
			}
		}
	}
}