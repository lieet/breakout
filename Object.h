#ifndef _OBJECT_H_
#define _OBJECT_H_

class Object {
public:
	float r, g, b;				// cores (r,g,b) do objeto

	virtual void Draw() {};
	virtual void Update() {};
};

#endif