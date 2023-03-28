#include <math.h>
#include <stdbool.h>

#include "SDL.h"
#include "SDL_ttf.h"

struct color
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

struct mousePosition
{
	uint32_t x;
	uint32_t y;
};

// Draws horiontal line on the color selector bar
void drawHorizontalZone(SDL_Renderer *renderer, int position)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect r1;
	r1.x = 0;
	r1.y = position-1;
	r1.w = 30;
	r1.h = 3;

	SDL_RenderFillRect(renderer, &r1);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_Rect r2;
	r2.x = 0;
	r2.y = position;
	r2.w = 30;
	r2.h = 1;

	SDL_RenderFillRect(renderer, &r2);
}

// Checks if mouse position is within bounds of specific zone
bool checkBounds(int xMin, int xMax, int yMin, int yMax, struct mousePosition mousePos)
{
	return (mousePos.x > xMin && mousePos.x < xMax && mousePos.y > yMin && mousePos.y < yMax);
}

// Draws the cross Hairs on the color square of where the current mouse position is
void colorSquareCrossHairs(SDL_Renderer *renderer, int colorBarWidth, int colorBarWidthSpace, int colorBarHeight, struct mousePosition currentPos)
{
	// Vertical white outline
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rwv;
	rwv.x = currentPos.x - 1;
	if(currentPos.x < colorBarWidth + colorBarWidthSpace)
	{
		rwv.x = colorBarWidth+colorBarWidthSpace;
	}
	rwv.y = 0;
	rwv.w = 3;
	rwv.h = colorBarHeight;

	SDL_RenderFillRect(renderer, &rwv);



	// Horizontal white outline
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rwh;
	rwh.x = colorBarWidth+colorBarWidthSpace;
	rwh.y = currentPos.y - 1;

	if(currentPos.y > colorBarHeight)
	{
		rwh.y = colorBarHeight-2;
	}

	rwh.w = colorBarHeight;
	rwh.h = 3;

	SDL_RenderFillRect(renderer, &rwh);

	// Vertical black outline
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_Rect rbv;
	rbv.x = currentPos.x;

	if(currentPos.x < colorBarWidth+colorBarWidthSpace)
	{
		rbv.x = colorBarWidth+colorBarWidthSpace;
	}

	rbv.y = 0;
	rbv.w = 1;
	rbv.h = colorBarHeight;

	SDL_RenderFillRect(renderer, &rbv);

	// Horizontal black outline
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_Rect rbh;
	rbh.x = colorBarWidth+colorBarWidthSpace;
	rbh.y = currentPos.y;

	if(currentPos.y > colorBarHeight)
	{
		rbh.y = colorBarHeight-1;
	}

	rbh.w = colorBarHeight;
	rbh.h = 1;

	SDL_RenderFillRect(renderer, &rbh);
}


void colorSquare(SDL_Renderer *renderer, float red, float green, float blue, int colorBarHeight, int colorBarWidth, int colorBarWidthSpace)
{
	int topLeft = colorBarWidth + colorBarWidthSpace;

	float xDifferenceRed = 255.0 - red;
	float xDifferenceGreen = 255.0 - green;
	float xDifferenceBlue = 255.0 - blue;

	float xRedDelta = xDifferenceRed/colorBarHeight;
	float xGreenDelta = xDifferenceGreen/colorBarHeight;
	float xBlueDelta = xDifferenceBlue/colorBarHeight;		

	xRedDelta = xDifferenceRed == 0 ?  0 : xRedDelta;
	xGreenDelta = xDifferenceGreen == 0 ?  0 : xGreenDelta;
	xBlueDelta = xDifferenceBlue == 0 ?  0 : xBlueDelta;

	float yDifferenceRed = 255.0;
	float yDifferenceGreen = 255.0;
	float yDifferenceBlue = 255.0;

	float yRedDelta = yDifferenceRed/colorBarHeight;
	float yGreenDelta = yDifferenceGreen/colorBarHeight;
	float yBlueDelta = yDifferenceBlue/colorBarHeight;

	float currentRed = 255.0;
	float currentGreen = 255.0;
	float currentBlue = 255.0;

	for(int y = 0; y < colorBarHeight; y++)
	{
		for(int x = 0; x < colorBarHeight; x++)
		{
			SDL_SetRenderDrawColor(renderer, currentRed, currentGreen, currentBlue, 255);
			SDL_RenderDrawPoint(renderer, topLeft + x, y);

			currentRed -= xRedDelta;
			currentGreen -= xGreenDelta;
			currentBlue -= xBlueDelta;

			currentRed = currentRed > 255.0 ? 255 : currentRed;
			currentGreen = currentGreen > 255.0 ? 255 : currentGreen;
			currentBlue = currentBlue > 255.0 ? 255 : currentBlue;

			currentRed = currentRed <  0 ? 0 : currentRed;
			currentGreen = currentGreen < 0 ? 0 : currentGreen;
			currentBlue = currentBlue < 0 ? 0 : currentBlue;

		}
		currentRed = 255 - (yRedDelta* (y+1));
		currentGreen = 255 - (yGreenDelta * (y+1));
		currentBlue = 255 - (yBlueDelta * (y+1));
	}

}

void colorOfCrossHairs(SDL_Renderer *renderer, struct color *colorIn, float red, float green, float blue, int colorBarHeight, int colorBarWidth, int colorBarWidthSpace, struct mousePosition currentPos)
{

	float xDifferenceRed = 255.0 - red;
	float xDifferenceGreen = 255.0 - green;
	float xDifferenceBlue = 255.0 - blue;

	float xRedDelta = xDifferenceRed/colorBarHeight;
	float xGreenDelta = xDifferenceGreen/colorBarHeight;
	float xBlueDelta = xDifferenceBlue/colorBarHeight;		

	xRedDelta = xDifferenceRed == 0 ?  0 : xRedDelta;
	xGreenDelta = xDifferenceGreen == 0 ?  0 : xGreenDelta;
	xBlueDelta = xDifferenceBlue == 0 ?  0 : xBlueDelta;

	float yDifferenceRed = 255.0;
	float yDifferenceGreen = 255.0;
	float yDifferenceBlue = 255.0;

	float yRedDelta = yDifferenceRed/colorBarHeight;
	float yGreenDelta = yDifferenceGreen/colorBarHeight;
	float yBlueDelta = yDifferenceBlue/colorBarHeight;

	float currentRed = 255.0;
	float currentGreen = 255.0;
	float currentBlue = 255.0;

	for(int y = 0; y < colorBarHeight; y++)
	{
		for(int x = 0; x < colorBarHeight; x++)
		{

			if(x == currentPos.x - colorBarWidth - colorBarWidthSpace && y == currentPos.y)
			{
				colorIn->red = currentRed;
				colorIn->green = currentGreen;
				colorIn->blue = currentBlue;
				return;
			}

			currentRed -= xRedDelta;
			currentGreen -= xGreenDelta;
			currentBlue -= xBlueDelta;

			currentRed = currentRed > 255.0 ? 255 : currentRed;
			currentGreen = currentGreen > 255.0 ? 255 : currentGreen;
			currentBlue = currentBlue > 255.0 ? 255 : currentBlue;

			currentRed = currentRed <  0 ? 0 : currentRed;
			currentGreen = currentGreen < 0 ? 0 : currentGreen;
			currentBlue = currentBlue < 0 ? 0 : currentBlue;

		}
		currentRed = 255 - (yRedDelta* (y+1));
		currentGreen = 255 - (yGreenDelta * (y+1));
		currentBlue = 255 - (yBlueDelta * (y+1));
	}
}

void positionColor(float *red, float *green, float *blue, int position, float num, float segmented)
{
	float tmpRed = 255;
	float tmpGreen = 0;
	float tmpBlue = 0;

	for(int i = 0; i < position; i++)
	{
		tmpBlue = i <= segmented ? tmpBlue + num : tmpBlue;
		tmpRed = (i >= segmented && i < 2*segmented) ? tmpRed - num : tmpRed;
		tmpGreen = i >= 2*segmented && i < 3*segmented ? tmpGreen + num : tmpGreen;
		tmpBlue = i >= 3*segmented && i < 4*segmented ? tmpBlue - num : tmpBlue;
		tmpRed = i >= 4*segmented && i < 5*segmented ? tmpRed + num : tmpRed;
		tmpGreen = i >= 5*segmented ? tmpGreen - num : tmpGreen;

		tmpRed = tmpRed >  255.0 ? 255 : round(tmpRed);
		tmpGreen = tmpGreen >  255.0 ? 255 : round(tmpGreen);
		tmpBlue = tmpBlue >  255.0 ? 255 : round(tmpBlue);

		tmpRed = tmpRed <  0 ? 0 : round(tmpRed);
		tmpGreen = tmpGreen < 0 ? 0 : round(tmpGreen);
		tmpBlue = tmpBlue < 0 ? 0 : round(tmpBlue);
	}

	*red = tmpRed;
	*green = tmpGreen;
	*blue = tmpBlue;
}

void verticalColorSelector(SDL_Renderer *renderer, float red, float green, float blue, int segmented, int colorBarWidth, float num, int colorBarHeight)
{
	for(int i = 0; i < colorBarHeight; i++)
	{
		SDL_SetRenderDrawColor(renderer, (int)red, (int)green, (int)blue, 255);

		SDL_Rect r;
		r.x = 0;
		r.y = i;
		r.w = colorBarWidth;
		r.h = 1;

		blue = i <= segmented ? blue + num : blue;
		red = (i >= segmented && i < 2*segmented) ? red - num : red;
		green = i >= 2*segmented && i < 3*segmented ? green + num : green;
		blue = i >= 3*segmented && i < 4*segmented ? blue - num : blue;
		red = i >= 4*segmented && i < 5*segmented ? red + num : red;
		green = i >= 5*segmented ? green - num : green;

		red = red >  255.0 ? 255 : round(red);
		green = green >  255.0 ? 255 : round(green);
		blue = blue >  255.0 ? 255 : round(blue);

		red = red <  0 ? 0 : round(red);
		green = green < 0 ? 0 : round(green);
		blue = blue < 0 ? 0 : round(blue);

		SDL_RenderFillRect(renderer, &r);
		//printf("rgb = %f %f %f\n %d\n", red, green, blue, i);
	}
}
void drawbuttonLabel(SDL_Renderer *renderer, TTF_Font *fontPointer, int buttonWidth, int buttonHeight, int buttonTopLeftY, int buttonTopLeftX, SDL_Color white)
{
	

	SDL_Surface *surfaceMessage = TTF_RenderText_Solid(fontPointer, "ok", white);

	SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);


	SDL_Rect rect;
	rect.x = buttonTopLeftX+(buttonWidth/4);
	rect.y = buttonTopLeftY+4;
	rect.w = buttonWidth/2;
	rect.h = buttonHeight-4;

	SDL_RenderCopy(renderer, message, NULL, &rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);
}

int drawButton(SDL_Renderer *renderer, int buttonWidth, int buttonHeight, int buttonTopLeftY, int buttonTopLeftX, struct color buttonColor)
{
	int colorChange = -35;
	int shadowSize = 3;

	uint8_t shadowRed = buttonColor.red + colorChange > 255 ? 255 : buttonColor.red + colorChange;
	uint8_t shadowGreen = buttonColor.green + colorChange > 255 ? 255 : buttonColor.green + colorChange;
	uint8_t shadowBlue = buttonColor.blue + colorChange > 255 ? 255 : buttonColor.blue + colorChange;

	SDL_SetRenderDrawColor(renderer, shadowRed, shadowGreen, shadowBlue, 255);

	SDL_Rect rBorder;
	rBorder.x = buttonTopLeftX - shadowSize;
	rBorder.y = buttonTopLeftY - shadowSize;
	rBorder.w = buttonWidth + shadowSize;
	rBorder.h = buttonHeight + shadowSize;

	SDL_RenderFillRect(renderer, &rBorder);

	// Main grey Section of button
	SDL_SetRenderDrawColor(renderer, buttonColor.red, buttonColor.green, buttonColor.blue, 255);

	SDL_Rect r;
	r.x = buttonTopLeftX;
	r.y = buttonTopLeftY;
	r.w = buttonWidth;
	r.h = buttonHeight;

	SDL_RenderFillRect(renderer, &r);

	return 0;
}

int colorPicker(struct color *selectedColor)
{
	struct color backgroundColor;
	backgroundColor.red = 100;
	backgroundColor.green = 100;
	backgroundColor.blue = 100;

	struct color buttonColor;
	buttonColor.red = 60;
	buttonColor.green = 60;
	buttonColor.blue = 60;

	bool leftMouseButtonDown = false;
	bool leftMouseButtonDownSquare = false;

	// Width of vertical color bar
	int colorBarWidth = 30;
	int currentColorHeight = colorBarWidth;

	// Height of vertical color bar
	int colorBarHeight = 500;

	int sizeOfCurrentColor = 60;

	// Position of mouse (Y-Axis) on vertical color bar
	int position = 0;

	// Colors initiated
	float red = 0;
	float green = 0;
	float blue = 0;

	// Vertical color bar changes in scale
	int numSections = 6;
	int segmented = colorBarHeight/numSections;
	float num = 255.0/((float)colorBarHeight/(float)numSections);

	// Width colorExample takes up at bottom of screen
	int colorSpaceBottom = 40;

	// Mouse position on color square
	struct mousePosition currentPos;
	currentPos.x = 0;
	currentPos.y = 0;


	// Gap between vertial color bar and color square
	int colorBarWidthSpace = 10;

	// Stores color value "cross-hairs" are on in the color square
	struct color crossHairs;
	crossHairs.red = 0;
	crossHairs.green = 0;
	crossHairs.blue = 0;

	bool running = true;
	SDL_Event event;

	struct mousePosition boundCheckPos;
	int buttonWidth, success;

	SDL_Color white = {255,255,255};

	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);	

	// Create a SDL window
	SDL_Window *window = SDL_CreateWindow("Color Picker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, colorBarHeight + colorBarWidth + colorBarWidthSpace, colorBarHeight + colorSpaceBottom, SDL_WINDOW_OPENGL);

	// Create a renderer (accelerated and in sync with the display refresh rate)
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//TTF_Init();
	if(TTF_Init()==-1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
	//TTF_Font *fontPointer = TTF_OpenFont("/home/mitch/colorWheel/SDL2_ColorPicker/ok.ttf", 24);    
	//TTF_Font *fontPointer = TTF_OpenFont("new.ttf", 20);
	TTF_Font *fontPointer = TTF_OpenFont("okFont.ttf", 20);

	if(fontPointer == NULL)
	{
		fprintf(stderr, "colorPicker: Failed to load font\n");
	}

	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					leftMouseButtonDown = false;
					leftMouseButtonDownSquare = false;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					// Used for bounds checking (within which section)
					boundCheckPos.x = event.motion.x;
					boundCheckPos.y = event.motion.y;

					if(checkBounds(0, colorBarWidth, 0, colorBarHeight, boundCheckPos))
					{
						leftMouseButtonDown = true;
					}
					if(checkBounds(colorBarWidth+colorBarWidthSpace, colorBarWidth+colorBarWidthSpace + colorBarHeight, 0, colorBarHeight, boundCheckPos))
					{
						leftMouseButtonDownSquare = true;
					}
					if(checkBounds(colorBarHeight - (colorBarWidth+colorBarWidthSpace), colorBarHeight + colorBarWidth + colorBarWidthSpace, colorBarHeight + colorBarWidthSpace, colorBarHeight + colorBarWidthSpace + colorBarWidth, boundCheckPos))
					{
						running = false;
					} 
				}
				break;
			case SDL_MOUSEMOTION:
				if (leftMouseButtonDown)
				{
					position = event.motion.y;
				}
				if (leftMouseButtonDownSquare)
				{
					currentPos.x = event.motion.x;
					currentPos.y = event.motion.y;				
				}
				break;
			default:
				break;
			}
		}

		red = 255.0; 
		green = 0.0;
		blue = 0.0; 

		SDL_RenderClear(renderer);

		verticalColorSelector(renderer, red, green, blue, segmented, colorBarWidth, num, colorBarHeight);
		position = position > colorBarHeight ? colorBarHeight : position;
		drawHorizontalZone(renderer, position);

		positionColor(&red, &green, &blue, position, num, segmented);

		colorSquare(renderer, red, green, blue, colorBarHeight, colorBarWidth, colorBarWidthSpace);

		colorSquareCrossHairs(renderer, colorBarWidth, colorBarWidthSpace, colorBarHeight, currentPos);

		crossHairs.red = 0;
		crossHairs.green = 0;
		crossHairs.blue = 0;

		colorOfCrossHairs(renderer, &crossHairs, red, green, blue, colorBarHeight, colorBarWidth, colorBarWidthSpace, currentPos);

		SDL_SetRenderDrawColor(renderer, crossHairs.red, crossHairs.green, crossHairs.blue, 255);


		SDL_Rect currentColorRectangle;
		currentColorRectangle.x = currentColorHeight + colorBarWidthSpace;
		currentColorRectangle.y = colorBarHeight + 10;
		currentColorRectangle.w = sizeOfCurrentColor;
		currentColorRectangle.h = colorBarWidth;

		SDL_RenderFillRect(renderer, &currentColorRectangle);

		buttonWidth = 3 * (colorBarWidth+colorBarWidthSpace);
		success = drawButton(renderer, buttonWidth, colorBarWidth, colorBarHeight + colorBarWidthSpace, colorBarHeight + colorBarWidth - buttonWidth, buttonColor);

		if(success != 0)
		{
			fprintf(stderr, "Drawing Button not successful\n");
		}		

		drawbuttonLabel(renderer, fontPointer, buttonWidth, colorBarWidth, colorBarHeight + colorBarWidthSpace, colorBarHeight + colorBarWidth - buttonWidth, white);

		SDL_SetRenderDrawColor(renderer, backgroundColor.red, backgroundColor.green, backgroundColor.blue, 255);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	TTF_CloseFont(fontPointer);

	selectedColor->red = crossHairs.red; 
	selectedColor->green = crossHairs.green;
	selectedColor->blue = crossHairs.blue;

	return 0;
}


// Remove main and integrate with program by calling colorPicker function
int main()
{
	struct color selectedColor;
	selectedColor.red = 0;
	selectedColor.green = 0;
	selectedColor.blue = 0;

	int success = colorPicker(&selectedColor);

	//Failure
	if(success != 0)
	{
		fprintf(stderr, "Something went wrong with colorPicker\n");
	}

	printf("(R, G, B) = (%d, %d, %d)\n", selectedColor.red, selectedColor.green, selectedColor.blue);

	return 0;
}

