#include <SDL2/SDL.h>
#include <math.h>



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

bool checkBounds(int xMin, int xMax, int yMin, int yMax, int x, int y)
{
	return (x > xMin && x < xMax && y > yMin && y < yMax);
}


void colorSquareCrossHairs(int width, int widthSpace, SDL_Renderer *renderer, int sizeOfColorBar, int mouseX, int mouseY)
{
	// Vertical white outline
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rwv;
   	rwv.x = mouseX-1;
	if(mouseX < width+widthSpace)
	{
		rwv.x = width+widthSpace;
	}
	rwv.y = 0;
	rwv.w = 3;
   	rwv.h = sizeOfColorBar;

	SDL_RenderFillRect(renderer, &rwv);

	// Horizontal white outline
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Rect rwh;
   	rwh.x = width+widthSpace;
	rwh.y = mouseY-1;
	if(mouseY > sizeOfColorBar)
	{
		rwh.y = sizeOfColorBar-2;
	}
	rwh.w = sizeOfColorBar;
   	rwh.h = 3;

	SDL_RenderFillRect(renderer, &rwh);


	// Vertical black outline
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_Rect rbv;
   	rbv.x = mouseX;
	if(mouseX < width+widthSpace)
	{
		rbv.x = width+widthSpace;
	}
	rbv.y = 0;
	rbv.w = 1;
   	rbv.h = sizeOfColorBar;

	SDL_RenderFillRect(renderer, &rbv);

	// Horizontal black outline
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_Rect rbh;
   	rbh.x = width+widthSpace;
	rbh.y = mouseY;
	if(mouseY > sizeOfColorBar)
	{
		rbh.y = sizeOfColorBar-1;
	}
	rbh.w = sizeOfColorBar;
   	rbh.h = 1;

	SDL_RenderFillRect(renderer, &rbh);
}


void colorSquare(float red, float green, float blue, SDL_Renderer *renderer, int sizeOfColorBar, int width, int widthSpace)
{
	int topLeft = width + widthSpace;

	float xDifferenceRed = 255.0 - red;
	float xDifferenceGreen = 255.0 - green;
	float xDifferenceBlue = 255.0 - blue;
	
	float xRedDelta = xDifferenceRed/sizeOfColorBar;
	float xGreenDelta = xDifferenceGreen/sizeOfColorBar;
	float xBlueDelta = xDifferenceBlue/sizeOfColorBar;		
			
	xRedDelta = xDifferenceRed == 0 ?  0 : xRedDelta;
	xGreenDelta = xDifferenceGreen == 0 ?  0 : xGreenDelta;
	xBlueDelta = xDifferenceBlue == 0 ?  0 : xBlueDelta;

	float yDifferenceRed = 255.0;
	float yDifferenceGreen = 255.0;
	float yDifferenceBlue = 255.0;

	float yRedDelta = yDifferenceRed/sizeOfColorBar;
	float yGreenDelta = yDifferenceGreen/sizeOfColorBar;
	float yBlueDelta = yDifferenceBlue/sizeOfColorBar;
	
	float currentRed = 255.0;
	float currentGreen = 255.0;
	float currentBlue = 255.0;

	for(int y = 0; y < sizeOfColorBar; y++)
	{
		for(int x = 0; x < sizeOfColorBar; x++)
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
		
void colorOfCrossHairs(int *redCH, int *greenCH, int *blueCH, float red, float green, float blue, SDL_Renderer *renderer, int sizeOfColorBar, int width, int widthSpace, int mouseX, int mouseY)
{
	
	int topLeft = width + widthSpace;

	float xDifferenceRed = 255.0 - red;
	float xDifferenceGreen = 255.0 - green;
	float xDifferenceBlue = 255.0 - blue;
	
	float xRedDelta = xDifferenceRed/sizeOfColorBar;
	float xGreenDelta = xDifferenceGreen/sizeOfColorBar;
	float xBlueDelta = xDifferenceBlue/sizeOfColorBar;		
			
	xRedDelta = xDifferenceRed == 0 ?  0 : xRedDelta;
	xGreenDelta = xDifferenceGreen == 0 ?  0 : xGreenDelta;
	xBlueDelta = xDifferenceBlue == 0 ?  0 : xBlueDelta;

	float yDifferenceRed = 255.0;
	float yDifferenceGreen = 255.0;
	float yDifferenceBlue = 255.0;

	float yRedDelta = yDifferenceRed/sizeOfColorBar;
	float yGreenDelta = yDifferenceGreen/sizeOfColorBar;
	float yBlueDelta = yDifferenceBlue/sizeOfColorBar;
	
	float currentRed = 255.0;
	float currentGreen = 255.0;
	float currentBlue = 255.0;

	for(int y = 0; y < sizeOfColorBar; y++)
	{
		for(int x = 0; x < sizeOfColorBar; x++)
		{

			if(x == mouseX-width-widthSpace && y == mouseY)
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

void verticalColorSelector(float red, float green, float blue, int segmented, SDL_Renderer *renderer, int width, float num, int sizeOfColorBar)
{
	for(int i = 0; i < sizeOfColorBar; i++)
	{
    	SDL_SetRenderDrawColor(renderer, (int)red, (int)green, (int)blue, 255);

	    SDL_Rect r;
   		r.x = 0;
	    r.y = i;
	    r.w = width;
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

int main(int argc, char **argv)
{
	bool leftMouseButtonDown = false;
	bool leftMouseButtonDownSquare = false;
    bool quit = false;

	int width = 30;

	int sizeOfCurrentColor = 60;

	int position = 0;
	
	int topLeft = 0;
	int bottonRight = 0;

	float red = 0; // Starting Color
	float green = 0;
	float blue = 0;

	int sizeOfColorBar = 400;
	int numSections = 6;
	int segmented = sizeOfColorBar/numSections;
	float num = 255.0/((float)sizeOfColorBar/(float)numSections);

	int colorSpaceBottom = 40;

	int mouseX = 0;
	int mouseY = 0;

	int widthSpace = 10;

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
	

    // Create a SDL window
    SDL_Window *window = SDL_CreateWindow("Color Picker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sizeOfColorBar + width + widthSpace, sizeOfColorBar + colorSpaceBottom, SDL_WINDOW_OPENGL);

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

		verticalColorSelector(red, green, blue, segmented, renderer, width, num, sizeOfColorBar);

		switch (event.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = false;
                    leftMouseButtonDownSquare = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
				{
					int xPos = event.motion.x;
					int yPos = event.motion.y;

					if(checkBounds(0, width, 0, sizeOfColorBar, xPos, yPos))
					{
                    	leftMouseButtonDown = true;
					}
					if(checkBounds(width+widthSpace, width+widthSpace + sizeOfColorBar, 0, sizeOfColorBar, xPos, yPos))
					{
                    	leftMouseButtonDownSquare = true;
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

		drawHorizontalZone(renderer, position);
	
		positionColor(&red, &green, &blue, position, num, segmented);
		
		colorSquare(red, green, blue, renderer, sizeOfColorBar, width, widthSpace);
		
		colorSquareCrossHairs(width, widthSpace, renderer, sizeOfColorBar, mouseX, mouseY);

		int redCH = 0;
		int greenCH = 0;
		int blueCH = 0;

		colorOfCrossHairs(&redCH, &greenCH, &blueCH, red, green, blue, renderer, sizeOfColorBar, width, widthSpace, mouseX, mouseY);
	
		printf("(R, G, B) = (%d, %d, %d)\n", redCH, greenCH, blueCH);

    	SDL_SetRenderDrawColor(renderer, redCH, greenCH, blueCH, 255);

	    SDL_Rect currentColorRectangle;
   		currentColorRectangle.x = width + widthSpace;
	    currentColorRectangle.y = sizeOfColorBar + 10;
	    currentColorRectangle.w = sizeOfCurrentColor;
    	currentColorRectangle.h = width;

		SDL_RenderFillRect(renderer, &currentColorRectangle);


    	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

