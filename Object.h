#ifndef _OBJECT_H_
#define _OBJECT_H_

class Object {
public:
	float x, y;					// (x, y) do centro do objeto
	float r, g, b;				// cores (r,g,b) do objeto
	float scalex, scaley, scalez;

	virtual void Draw() {};
	virtual void DrawBoundingBox() {};
	virtual void Update() {};
	virtual void Move(float, float) {};
	virtual float getXi() {};
	virtual float getXf() {};
	virtual float getYi() {};
	virtual float getYf() {};
};

#endif