#include"Utility.h"
#include "Path.h"
#include "PathView.h"
#include "Visualizer.h"
#include "DataOutput.h"

#ifdef WINDOW

#define MAX_CONDITION 4
#define MAX_TRIAL 3 //index 0,1...
#define MAX_SUBJECT 15
//#define DATA_FOLDER "Res/RawData/Test/"
//#define DATA_FOLDER "Res/RawData/First Study/"
#define DATA_FOLDER "Res/RawData/Second Study/"

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Path Visualization");
	/////////////////////////////////Panel///////////////////////////////////
	//background
	sf::RectangleShape background;
	background.setSize(sf::Vector2f(WINDOW_WIDTH - CANVAS_WIDTH, WINDOW_HEIGHT));
	sf::Color backgroundColor = sf::Color::Black;
	backgroundColor.a = 30;
	background.setFillColor(backgroundColor);
	background.setPosition(CANVAS_WIDTH, 0);

	tgui::Gui gui(window); 
	if (gui.setGlobalFont("Res/TGUI/fonts/DejaVuSans.ttf") == false)
		return 1;

	//condition
	//label
	tgui::Label::Ptr conditionLabel(gui);
	conditionLabel->load(THEME_CONFIG_FILE);
	conditionLabel->setText("Condition");
	conditionLabel->setPosition(CANVAS_WIDTH+10, 20);
	conditionLabel->setTextColor(sf::Color::Blue);
	conditionLabel->setTextSize(24);
	//condition list
	tgui::ListBox::Ptr conditionList(gui);
	conditionList->load(THEME_CONFIG_FILE);
	conditionList->setSize(150, 200);
	conditionList->setItemHeight(30);
	conditionList->setPosition(CANVAS_WIDTH + 10, 50);
	for (int i = 1; i <= 8; i++)
	{
		char tmp[2];
		string str = string(itoa(i,tmp,10));
		conditionList->addItem(str);
	}
	string selectedCondition = "";

	//trial
	//label
	tgui::Label::Ptr trialLabel(gui);
	trialLabel->load(THEME_CONFIG_FILE);
	trialLabel->setText("Layout");
	trialLabel->setPosition(CANVAS_WIDTH + 10, 260);
	trialLabel->setTextColor(sf::Color::Blue);
	trialLabel->setTextSize(24);
	//condition list
	tgui::ListBox::Ptr trialList(gui);
	trialList->load(THEME_CONFIG_FILE);
	trialList->setSize(150, 200);
	trialList->setItemHeight(30);
	trialList->setPosition(CANVAS_WIDTH + 10, 290);
	for (int i = 0; i <= 7; i++)
	{
		char tmp[2];
		string str = string(itoa(i, tmp, 10));
		trialList->addItem(str);
	}
	string selectedTrial = "";

	tgui::Button::Ptr button(gui);
	button->load(THEME_CONFIG_FILE);
	button->setPosition(CANVAS_WIDTH + 10, 500);
	button->setText("Screenshot");
	button->setCallbackId(1);
	button->setTextSize(15);
	button->bindCallback(tgui::Button::LeftMouseClicked);
	button->setSize(90, 50);

	int conditionIndex = 1;
	int trialIndex = 0;
	int subjectIndex = 0;
	int timer = 0;
	int timerEach = 5;
	int filteredNumber = 1;

	DataOutput dataOutput;

	/////////////////////////////////Visualizer///////////////////////////////////
	Visualizer visualizer(DATA_FOLDER, window, dataOutput);
	
	//output csv
	dataOutput.flush("Res/Result/Performance.csv");

	//first study test
	visualizer.filter(7, 7, 0);//pass
	//visualizer.filter(4, 0, 16);//pass
	//visualizer.filter(3, 1, 23);
	//second study test
	//visualizer.filter(3, 3, 0);
	//visualizer.filter(1, 0, 15);
	//visualizer.filter(0, 2, 7);
	//visualizer.setDrawMode("Polyline");
	visualizer.setDrawMode("Triangle");

	while (window.isOpen())
	{
		
		/////////////////////////////////Batch Begin///////////////////////////////////
		//screenshot export
		//if (timer < -10) //temp
		//{
		//	visualizer.filter(conditionIndex, trialIndex, subjectIndex);
		//	

		//	//auto
		//	if (conditionIndex <= MAX_CONDITION && trialIndex <= MAX_TRIAL && subjectIndex <= MAX_SUBJECT)
		//	{
		//		if (timerEach <= 0)
		//		{
		//			//screenshot
		//			if (filteredNumber)
		//			{
		//				sf::Image screenshot = window.capture();
		//				std::stringstream filename;
		//				filename << "Res/screenshots/sub "<<subjectIndex<<" cond " << conditionIndex << " layout " << trialIndex << ".jpg";
		//				screenshot.saveToFile(filename.str());
		//				
		//			}

		//			//add next
		//			if (conditionIndex == MAX_CONDITION && trialIndex == MAX_TRIAL)
		//			{
		//				subjectIndex++;
		//				conditionIndex = 1;
		//				trialIndex = 0;
		//			}
		//			else 
		//			{
		//				if (trialIndex == MAX_TRIAL)
		//				{
		//					conditionIndex++;
		//					trialIndex = 0;
		//				}
		//				else
		//				{
		//					trialIndex++;
		//				}
		//			}

		//			filteredNumber = visualizer.filter(conditionIndex, trialIndex, subjectIndex);
		//			cout << subjectIndex<<" "<<conditionIndex<<" "<<trialIndex<<" Number: " << filteredNumber << endl;
		//			timerEach = 5;
		//		}
		//		else
		//		{
		//			timerEach--;
		//		}
		//	}
		//}
		//else
		//{
		//	timer++;
		//}
		/////////////////////////////////Batch End///////////////////////////////////
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			/////////////////////////////////Visualizer///////////////////////////////////
			visualizer.processEvent(event);
			/////////////////////////////////Panel///////////////////////////////////
			gui.handleEvent(event);
		}

		//for gui real-time interaction
		//if (conditionList->getSelectedItem() != selectedCondition || trialList->getSelectedItem() != selectedTrial)
		//{
		//	string condition = conditionList->getSelectedItem();
		//	//cout << "Selected: " << string(conditionList->getSelectedItem()) << endl;
		//	selectedCondition = condition;
		//	string trial = trialList->getSelectedItem();
		//	selectedTrial = trial;
		//	visualizer.filter(atoi(condition.c_str()), atoi(trial.c_str()));
		//}

		tgui::Callback callback;
		while (gui.pollCallback(callback))
		{
			if (callback.id == 1)
			{
				cout << "Screenshot: " << endl;
				sf::Image screenshot = window.capture();
				std::stringstream filename;
				filename << "Res/screenshots/cond " << selectedCondition<<" layout "<<selectedTrial << ".jpg";
				screenshot.saveToFile(filename.str());
			}
		}

		window.clear(sf::Color::White);
		gui.draw();
		/////////////////////////////////Visualizer///////////////////////////////////
		visualizer.draw();
		/////////////////////////////////Panel///////////////////////////////////
		// Draw all created widgets
		
		window.draw(background);
		
		window.display();

		
		}


	return 0;
}

#endif