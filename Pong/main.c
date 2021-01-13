//main.c

#include "gba.h"
#include <stdbool.h>

void sync() {
	//only modify VRAM if in V_BUFFER
	//typically we would put logic, physics, ai
	while (REG_DISPLAY_VCOUNT >= 160);
	while (REG_DISPLAY_VCOUNT < 160);
}

uint16 makeColor(uint8 r, uint8 g, uint8 b) {
	return (r & 0x1f) | ((g & 0x1f) << 5) | ((b & 0x1f) << 10);
}

uint32 clamp(uint32 value, uint32 min, uint32 max) {
	return (value < min ? min : (value > max ? max : value));
}

void drawRect(struct Rect rect, uint16 color) {
	for (int y = 0; y < rect.h; y++) {
		for (int x = 0; x < rect.w; x++) {
			SCREENBUFFER[(rect.y + y) * SCREEN_WIDTH + rect.x + x] = color;
		}
	}
}

void init7seg() {
	a.w = 16;
	a.h = 4;
	f.w = 4;
	f.h = 16;
	
	b = c = e = f;
	d = g = a;
	
	a.x = d.x = e.x = f.x = g.x = SCREEN_WIDTH/4;
	b.x = c.x = a.x + a.w;
	
	a.y = b.y = f.y = 0;
	c.y = e.y = g.y = b.y + b.h - a.h;
	d.y = g.y + b.h - a.h;
	
	a1.w = 16;
	a1.h = 4;
	f1.w = 4;
	f1.h = 16;
	
	b1 = c1 = e1 = f1;
	d1 = g1 = a1;
	
	a1.x = d1.x = e1.x = f1.x = g1.x = SCREEN_WIDTH - (SCREEN_WIDTH/3);
	b1.x = c1.x = a1.x + a1.w;
	
	a1.y = b1.y = f1.y = 0;
	c1.y = e1.y = g1.y = b1.y + b1.h - a1.h;
	d1.y = g1.y + b1.h - a1.h;
}

void clear7seg() {
	drawRect(a, makeColor(0, 0, 0));
	drawRect(b, makeColor(0, 0, 0));
	drawRect(c, makeColor(0, 0, 0));
	drawRect(d, makeColor(0, 0, 0));
	drawRect(e, makeColor(0, 0, 0));
	drawRect(f, makeColor(0, 0, 0));
	drawRect(g, makeColor(0, 0, 0));
	drawRect(a1, makeColor(0, 0, 0));
	drawRect(b1, makeColor(0, 0, 0));
	drawRect(c1, makeColor(0, 0, 0));
	drawRect(d1, makeColor(0, 0, 0));
	drawRect(e1, makeColor(0, 0, 0));
	drawRect(f1, makeColor(0, 0, 0));
	drawRect(g1, makeColor(0, 0, 0));
}

void draw7seg(uint8 num, uint8 num2) {
	
	clear7seg();
	bool w, x, y, z, w1, x1, y1, z1;
	
	//? is inline if statement
	//first value after returned if true, value after colon returned if false
	w = (num >= 8 ? ((num -= 8) ? 1 : 1) : 0);
	x = (num >= 4 ? ((num -= 4) ? 1 : 1) : 0);
	y = (num >= 2 ? ((num -= 2) ? 1 : 1) : 0);
	z = (num >= 1 ? ((num -= 1) ? 1 : 1) : 0);
	w1 = (num2 >= 8 ? ((num2 -= 8) ? 1 : 1) : 0);
	x1 = (num2 >= 4 ? ((num2 -= 4) ? 1 : 1) : 0);
	y1 = (num2 >= 2 ? ((num2 -= 2) ? 1 : 1) : 0);
	z1 = (num2 >= 1 ? ((num2 -= 1) ? 1 : 1) : 0);
	
	//where if statements go
	if (w || y || (!x && !z) || (x && z))
		drawRect(a, makeColor(0x1f, 0x1f, 0x1f));
	if ((y && z) || (!y && !z) || !x)
		drawRect(b, makeColor(0x1f, 0x1f, 0x1f));
	if (x || !y || z)
		drawRect(c, makeColor(0x1f, 0x1f, 0x1f));
	if (w || (y && !z) || (!x && !z) || (!x && y) || (x && !y && z))
		drawRect(d, makeColor(0x1f, 0x1f, 0x1f));
	if ((y && !z) || (!x && !z))
		drawRect(e, makeColor(0x1f, 0x1f, 0x1f));
	if (w || (x && !y) || (x && !z) || (!y && !z))
		drawRect(f, makeColor(0x1f, 0x1f, 0x1f));
	if (w || (!y && x) || (y && !z) || (y && !x))
		drawRect(g, makeColor(0x1f, 0x1f, 0x1f));
	
	if (w1 || y1 || (!x1 && !z1) || (x1 && z1))
		drawRect(a1, makeColor(0x1f, 0x1f, 0x1f));
	if ((y1 && z1) || (!y1 && !z1) || !x1)
		drawRect(b1, makeColor(0x1f, 0x1f, 0x1f));
	if (x1 || !y1 || z1)
		drawRect(c1, makeColor(0x1f, 0x1f, 0x1f));
	if (w1 || (y1 && !z1) || (!x1 && !z1) || (!x1 && y1) || (x1 && !y1 && z1))
		drawRect(d1, makeColor(0x1f, 0x1f, 0x1f));
	if ((y1 && !z1) || (!x1 && !z1))
		drawRect(e1, makeColor(0x1f, 0x1f, 0x1f));
	if (w1 || (x1 && !y1) || (x1 && !z1) || (!y1 && !z1))
		drawRect(f1, makeColor(0x1f, 0x1f, 0x1f));
	if (w1 || (!y1 && x1) || (y1 && !z1) || (y1 && !x1))
		drawRect(g1, makeColor(0x1f, 0x1f, 0x1f));
}

int main() {
	
	REG_DISPLAY = VIDEOMODE | BGMODE;
	
	//init a for testing
	init7seg();
	uint8 valPlayer = 0;
	uint8 valComputer = 0;
	
	//setting up temp variables for Ball
	uint32 ballLeft = 120;
	uint32 ballTop = 80;
	udou8 speedX = 1;
	udou8 speedY = 1;
	
	//setting up values for player
	uint32 top = 0;
	uint32 left = 0;
	
	//setting values for computer
	uint32 topC = 0;
	uint32 leftC = SCREEN_WIDTH - computer.w;
	
	//player is 32 pixel height, 8 pixels wide
	player.h = 32;
	player.w = 8;
	player.x = 0;
	player.y = 0;
	uint16 p_color = makeColor(0x12, 0, 0); //(red, green, blue)
	
	//computer is 32 pixels high, 8 wide
	computer.h = 32;
	computer.w = 8;
	computer.x = SCREEN_WIDTH - computer.w;
	computer.y = 0;
	uint16 c_color = makeColor(0, 0x1f, 0x1f);
	
	//ball is 8 pixels square
	ball.h = 8;
	ball.w = 8;
	ball.x = ballLeft;
	ball.y = ballTop;
	prevBall = ball;
	uint16 b_color = makeColor(0x1f, 0x1f, 0);
	
	while(1) {
		sync();
		
		//erase prev object position
		drawRect(prevBall, makeColor(0,0,0));
		drawRect(prevPlayer, makeColor(0,0,0));
		drawRect(prevComputer, makeColor(0,0,0));
		
		//set ball to speed
		ballTop += speedY;
		ballLeft += speedX;
		
		//ai response
		if (ballLeft >= SCREEN_WIDTH - (SCREEN_WIDTH/2)) {
			if ((ballTop - (ball.h/2)) > topC) {
				topC++;
			} else if ((ballTop - (ball.h/2)) < topC) {
				topC--;
			}
		}
		
		//register key input
		if (!(REG_KEY_INPUT & DOWN))
			top++;
		if (!(REG_KEY_INPUT & UP))
			top--;
		
		//top clamp for player & pc
		top = clamp(top, 1, SCREEN_HEIGHT - player.h);
		topC = clamp(topC, 1, SCREEN_HEIGHT - computer.h);
		
		//check collision stuff
		ballTop = clamp(ballTop, 0, SCREEN_HEIGHT - ball.h);
		ballLeft = clamp(ballLeft, 0, SCREEN_WIDTH - ball.w);
		
		//flips ball velocity on top/bottom
		if (ballTop == 0 || ballTop == SCREEN_HEIGHT - ball.h)
			speedY = -speedY;
		//resets if computer scores
		if (ballLeft == 0) {
			valComputer++;
			ballLeft = 120;
			ballTop = 80;
			speedX = -1;
			speedY = -1;
		}
		//resets if player scores
		if (ballLeft == SCREEN_WIDTH - ball.w) {
			valPlayer++;
			ballLeft = 120;
			ballTop = 80;
			speedX = 1;
			speedY = 1;
		}
		
		//resets when someone wins
		if (valPlayer == 7 || valComputer == 7) {
			valPlayer = 0;
			valComputer = 0;
			ballLeft = 120;
			ballTop = 80;
			if (speedX == 0)
				speedX = -1;
			else
				speedX = 1;
			if (speedY < 0)
				speedY = -1;
			else
				speedY = 1;
		}
		
		ball.x = ballLeft;
		ball.y = ballTop;
		prevBall = ball;
		
		//collision for player
		if (ball.x == player.w) {
			if (ball.y < player.y + player.h && ball.y + ball.h > player.y) {
				speedX = -speedX;
				if (speedX < 2 && speedY < 2) {
					speedX += .1;
					speedY += .1;
					if (speedY == 0)
						speedY = 1;
				}
			}
		}
		//collision for computer
		if (ball.x + ball.w == SCREEN_WIDTH - computer.w) {
			if (ball.y < computer.y + computer.h && ball.y + ball.h > computer.y) {
				speedX = -speedX;
				if (speedX > -2 && speedY > -2) {
					speedX -= .1;
					speedY -= .1;
					if (speedY == 0)
						speedY = 1;
				}
			}
		}
		
		player.y = top;
		prevPlayer = player;
		computer.y = topC;
		prevComputer = computer;
		
		//draw area
		draw7seg(valPlayer, valComputer);
		drawRect(player, p_color);
		drawRect(ball, b_color);
		drawRect(computer, c_color);
	}
}