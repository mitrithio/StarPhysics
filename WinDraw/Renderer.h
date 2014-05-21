#ifndef RENDERER_H
#define RENDERER_H

class Bitmap; 

class Renderer
{
public: 
	virtual void OnRender(Bitmap* renderTarget) = 0; 
}; 

#endif