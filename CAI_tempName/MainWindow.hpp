#pragma once
#include"Window.h"
#include"Button.h"
#include "Grid.h"

class MainWindow : public Window
{
public:
	MainWindow(int width=800,int height=600) noexcept :Window(width, height) {
		initializeComponents();

		///测试代码
		Grid* grid = new Grid();
		grid->setGridRCCollection(3, 3);
		grid->setBackground(Brush(Draw::Color::BLUE));
		setContent(*grid);
		Grid* grid2 = new Grid();
		grid2->setBackground(Brush(0xffff00ff));
		grid->setRC(grid2, 1, 1);
		Button* btn = new Button();
		btn->setWidth(500);
		btn->setHeight(20);
		btn->setZindex(12);
		//btn->setContent(L"你好");
		grid2->addChild(*btn);
		grid2->setBorderSize(10);
		btn->setBackground(Brush(Draw::Color::GREEN));
		grid->addChild(*grid2);
		///
	}
	~MainWindow() noexcept {
	}
private:
	void initializeComponents(void) {
		//以下设置每个窗口都会有一个，其目的是将坐标映射到标准设备坐标
		name = "MainWindow";
	}

};
