#pragma once
struct GLFWwindow;
class MouseMoveEvent;
class RenderEngine;
class UIElement;
/// <summary>
/// 程序控制中心
/// 会监听鼠标移动
/// </summary>
class Application
{
public:
	static Application app;
public:
	void Terminat();
	void Start();
public:
	bool Init();
/// <summary>
/// 对原始的事件数据进行处理
/// </summary>
public:
	void OnMouseMove(UIElement* win,double x,double y);
	void OnMouseClick(int button, int buttonStatus, int mods);
	void OnWindowLeave(UIElement* win);
	void OnKeyInput(int key, int scancode, int action, int mods);
	void OnTextInput(unsigned int code);
private:
	Application();
	~Application();
private:
	//处理鼠标移动事件
	void MousePositionHandle(MouseMoveEvent& e, UIElement*& element,size_t mousOverElemntIndex);
	inline void MouseButtonHandle(int button,int buttonStatus,int mods);
	inline void RaisePreMouseOverEvent(UIElement& element,const int& x ,const int& y);
	inline void RaiseMouseOverEvent(UIElement& element,const int& x,const int& y);
	inline void RaiseMouseEnterEvent(UIElement& element);
	inline void RaiseMouseLeaveEvent(UIElement& element);
	inline void RaisePreMouseDownEvent(int button,int mods);
	inline void RaisePreMouseUpEvent(int button, int mods);
	inline void RaiseMouseDownEvent(int button,int mods);
	inline void RaiseMouseUpEvent(int button,int mods);
	inline void RaiseKeyInputEvent(UIElement& element, int key, int action, int mods);
	inline void RaiseTextInputEvent(UIElement& element, unsigned int code);
public:
	RenderEngine* renderEngine;
private:
	//鼠标直接指向的控件
	UIElement* mouseDirectOverElement;
	//焦点控件
	UIElement* focusElement;
	std::deque<UIElement*> mouseOverElements;
};

void LeaveWindowCallBack(GLFWwindow* winHD, int entered);
void KeyInputCallBack(GLFWwindow* winHD, int key, int scancode, int action, int mods);
void TextInputCallBack(GLFWwindow* winHD, unsigned int code);
void MouseMoveCallBack(GLFWwindow* winHD, double xpos, double ypos);
void MouseButtonCallBack(GLFWwindow* winHD, int button , int status, int mods);