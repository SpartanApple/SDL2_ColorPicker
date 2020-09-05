#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>


struct color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
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
bool checkBounds(int xMin, int xMax, int yMin, int yMax, int x, int y)
{
	return (x > xMin && x < xMax && y > yMin && y < yMax);
}

// Draws the cross Hairs on the color square of where the current mouse position is
void colorSquareCrossHairs(SDL_Renderer *renderer, int colorBarWidth, int colorBarWidthSpace, int colorBarHeight, int mouseX, int mouseY)
{
	// Vertical white outline
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rwv;
   	rwv.x = mouseX-1;
	if(mouseX < colorBarWidth+colorBarWidthSpace)
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
	rwh.y = mouseY-1;
	if(mouseY > colorBarHeight)
	{
		rwh.y = colorBarHeight-2;
	}
	rwh.w = colorBarHeight;
   	rwh.h = 3;

	SDL_RenderFillRect(renderer, &rwh);





	// Vertical black outline
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_Rect rbv;
   	rbv.x = mouseX;
	if(mouseX < colorBarWidth+colorBarWidthSpace)
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
	rbh.y = mouseY;
	if(mouseY > colorBarHeight)
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
		
void colorOfCrossHairs(SDL_Renderer *renderer, int *redCH, int *greenCH, int *blueCH, float red, float green, float blue, int colorBarHeight, int colorBarWidth, int colorBarWidthSpace, int mouseX, int mouseY)
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

			if(x == mouseX-colorBarWidth-colorBarWidthSpace && y == mouseY)
			{
				*redCH = currentRed;
				*greenCH = currentGreen;
				*blueCH = currentBlue;
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

void oDraw(SDL_Renderer *renderer, int topLeftY, int topLeftX, int red, int green, int blue)
{
	SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
	
	SDL_RenderDrawPoint(renderer, topLeftX + 35, topLeftY + 8);
	SDL_RenderDrawPoint(renderer, topLeftX + 36, topLeftY + 8);
	SDL_RenderDrawPoint(renderer, topLeftX + 37, topLeftY + 8);
	SDL_RenderDrawPoint(renderer, topLeftX + 38, topLeftY + 8);
	SDL_RenderDrawPoint(renderer, topLeftX + 37, topLeftY + 9);
	SDL_RenderDrawPoint(renderer, topLeftX + 38, topLeftY + 9);
	SDL_RenderDrawPoint(renderer, topLeftX + 39, topLeftY + 10);


}

int drawButton(SDL_Renderer *renderer, int buttonWidth, int buttonHeight, int buttonTopLeftY, int buttonTopLeftX, int buttonRed, int buttonGreen, int buttonBlue)
{
	int colorChange = -35;
	int shadowSize = 3;

	uint8_t shadowRed = buttonRed + colorChange > 255 ? 255 : buttonRed + colorChange;
	uint8_t shadowGreen = buttonGreen + colorChange > 255 ? 255 : buttonGreen + colorChange;
	uint8_t shadowBlue = buttonBlue + colorChange > 255 ? 255 : buttonBlue + colorChange;

    SDL_SetRenderDrawColor(renderer, shadowRed, shadowGreen, shadowBlue, 255);

	SDL_Rect rBorder;
   	rBorder.x = buttonTopLeftX - shadowSize;
	rBorder.y = buttonTopLeftY - shadowSize;
	rBorder.w = buttonWidth + shadowSize;
    rBorder.h = buttonHeight + shadowSize;
	
	SDL_RenderFillRect(renderer, &rBorder);

	// Main grey Section of button
    SDL_SetRenderDrawColor(renderer, buttonRed, buttonGreen, buttonBlue, 255);

	SDL_Rect r;
   	r.x = buttonTopLeftX;
	r.y = buttonTopLeftY;
	r.w = buttonWidth;
    r.h = buttonHeight;
	
	SDL_RenderFillRect(renderer, &r);

	return 0;
}

int colorPicker(int *finalRed, int *finalGreen, int *finalBlue)
{
	uint8_t backgroundRed = 100;
	uint8_t backgroundGreen = 100;
	uint8_t backgroundBlue = 100;

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
	int mouseX = 0;
	int mouseY = 0;

	// Gap between vertial color bar and color square
	int colorBarWidthSpace = 10;

	// Stores color value "cross-hairs" are on in the color square
	//int redCH = 0;
	//int greenCH = 0;
	//int blueCH = 0;

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);	

    // Create a SDL window
    SDL_Window *window = SDL_CreateWindow("Color Picker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, colorBarHeight + colorBarWidth + colorBarWidthSpace, colorBarHeight + colorSpaceBottom, SDL_WINDOW_OPENGL);

    // Create a renderer (accelerated and in sync with the display refresh rate)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    bool running = true;
    SDL_Event event;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
        }
		red = 255.0; 
        green = 0.0;
        blue = 0.0; 

		SDL_RenderClear(renderer);

		verticalColorSelector(renderer, red, green, blue, segmented, colorBarWidth, num, colorBarHeight);

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
                	break;
				}
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
				{
					// Used for bounds checking (within which section)
					int xPos = event.motion.x;
					int yPos = event.motion.y;

					if(checkBounds(0, colorBarWidth, 0, colorBarHeight, xPos, yPos))
					{
                    	leftMouseButtonDown = true;
					}
					if(checkBounds(colorBarWidth+colorBarWidthSpace, colorBarWidth+colorBarWidthSpace + colorBarHeight, 0, colorBarHeight, xPos, yPos))
					{
                    	leftMouseButtonDownSquare = true;
					}
					if(checkBounds(colorBarHeight - (colorBarWidth+colorBarWidthSpace), colorBarHeight + colorBarWidth + colorBarWidthSpace, colorBarHeight + colorBarWidthSpace, colorBarHeight + colorBarWidthSpace + colorBarWidth, xPos, yPos))
					{
						running = false;
					} 
				}
            case SDL_MOUSEMOTION:
				if (leftMouseButtonDown)
                {
                    position = event.motion.y;
                }
				if (leftMouseButtonDownSquare)
				{
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;				
				}
                break;
        }
		position = position > colorBarHeight ? colorBarHeight : position;
		drawHorizontalZone(renderer, position);
	
		positionColor(&red, &green, &blue, position, num, segmented);
		
		colorSquare(renderer, red, green, blue, colorBarHeight, colorBarWidth, colorBarWidthSpace);
		
		colorSquareCrossHairs(renderer, colorBarWidth, colorBarWidthSpace, colorBarHeight, mouseX, mouseY);

		redCH = 0;
		greenCH = 0;
		blueCH = 0;

		colorOfCrossHairs(renderer, &redCH, &greenCH, &blueCH, red, green, blue, colorBarHeight, colorBarWidth, colorBarWidthSpace, mouseX, mouseY);
	
    	SDL_SetRenderDrawColor(renderer, redCH, greenCH, blueCH, 255);
		

	    SDL_Rect currentColorRectangle;
   		currentColorRectangle.x = currentColorHeight + colorBarWidthSpace;
	    currentColorRectangle.y = colorBarHeight + 10;
	    currentColorRectangle.w = sizeOfCurrentColor;
    	currentColorRectangle.h = colorBarWidth;

		SDL_RenderFillRect(renderer, &currentColorRectangle);
		

		int buttonWidth = 3 * (colorBarWidth+colorBarWidthSpace);
		int sucess = drawButton(renderer, buttonWidth, colorBarWidth, colorBarHeight + colorBarWidthSpace, colorBarHeight + colorBarWidth - buttonWidth, 60, 60, 60);
		if(sucess != 0)
		{
			fprintf(stderr, "Drawing Button not sucessful");
		}		

		oDraw(renderer, colorBarHeight + colorBarWidthSpace, colorBarHeight + colorBarWidth - buttonWidth, 255, 255, 255);


    	SDL_SetRenderDrawColor(renderer, backgroundRed, backgroundGreen, backgroundBlue, 255);
		
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

	*finalRed = redCH; 
	*finalGreen = greenCH;
	*finalBlue = blueCH;

    return 0;
}


// Remove main and integrate with program by calling colorPicker function
int main()
{
	int red   = 0;
	int green = 0;
	int blue  = 0;

	int sucess = colorPicker(&red, &green, &blue);
	
	//Failure
	if(sucess != 0)
	{
		fprintf(stderr, "Something went wrong with colorPicker\n");
	}

	printf("(R, G, B) = (%d, %d, %d)\n", red, green, blue);

	return 0;
}

