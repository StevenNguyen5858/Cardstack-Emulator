#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


using namespace std;


/*	Group0: SNProcessing and SNElement tool explanation.
*
*	Group1: SNProcessing global variables and functions.
*
*	Group2: SNElement classes: SNElement, SNButton, SNLabel, SNContainer, SNCache,
*			SNPage and SNApp class.
*
*	Group3: SNElement navigation page creation. */


// ********************************************************************************************
// Group0: SNProcessing and SNElement tool explanation.

/*	Explanation for using this SNProcessing and SNElements tool:
*	-This file's purpose is to emmulate the Processing 3.5.4 IDE. Until further
*	implementation, processing.org can be used as a close documentation reference.
*	Note that the main.cpp is setup similar to that IDE, main.cpp should
*	only be modified by writing code in the following functions:
*	-void setup() Runs once at the initial instance before the application driver begins.
*	-void draw() Runs continously as apart of the application driver.
*	-The next functions are event handlers. They run prior to each draw() frame.
*	-void mouse_pressed() Runs on the event the mouse is pressed.
*	-void mouse_released() Runs on the event the mouse is released.
*	Avoid modification of main(), unless planning to use unimplemented SFML features. */

/*	SNElements description:
*	A Foundational project for future C++ application projects (GUI library extension).
*	This project relies on the SFML low level Graphics library. SFML is a library which
*	handles primitive objects such as geometric shapes, image sprites and application windows.
*	SNElements uses SFML to handle higher level objects such as pages and the elements
*	that may be within them: buttons, radio buttons, sliders, lables, etc.
*
*	For those wishing to use unimplemented SFML features keep in mind, SNProcessing renders to
*	a single application/RenderWindow. Multi-window applications will be supported in a
*	different version. */


// ********************************************************************************************
// Group1: SNProcessing global variablesand functions.

// Single instance of Prcessing begins here. It includes global style values: 
sf::RenderWindow main_window;
sf::Color current_fill = sf::Color(255, 255, 255, 255);
sf::Color current_stroke = sf::Color(0, 0, 0, 255);
int current_stroke_weight = 2;
sf::Font font;

/* gridW and gridH represent the number of grid units will fit in the current screen.
*  Using the number of grid units, we determine the pixels per unit for the x and y axies.
*  We can use this value in our projections to keep elements at a scale.
*/
int gridW = 32;
int gridH = 18;
int sw;
int sh;
int displayW = sf::VideoMode::getDesktopMode().width;
int displayH = sf::VideoMode::getDesktopMode().height;

// Image icons:
sf::Image icon_image;
sf::Image icon_sound;
sf::Image icon_text;
sf::Image icon_video;

sf::Image radio_empty;
sf::Image radio_full;

sf::Image bg2;
sf::Image bg4;

// Sets up the basic screen dimentions, then on the front end use is setting grid units sw and sh.
void refresh_grid() {
	int screen_width = main_window.getSize().x;
	int screen_height = main_window.getSize().y;
	sw = screen_width / gridW;
	sh = screen_height / gridH;
}
void setup_window(int screen_width, int screen_height, string title) {
	bool couldnt_load = false;
	if (!bg2.loadFromFile("SNElement Resources/BG2.png")) {
		sf::err() << "Couldn't load BG2\n";
		bool couldnt_load = true;
	}
	if (!bg4.loadFromFile("SNElement Resources/BG4.jpg")) {
		sf::err() << "Couldn't load BG4\n";
		bool couldnt_load = true;
	}
	if (!font.loadFromFile("SNElement Resources/cour.ttf")) {
		sf::err() << "Couldn't load cour font\n";
		bool couldnt_load = true;
	}
	if (!icon_image.loadFromFile("SNElement Resources/ImageIcon.png")) {
		sf::err() << "Couldn't load ImageIcon\n";
		bool couldnt_load = true;
	}
	if (!icon_sound.loadFromFile("SNElement Resources/SoundIcon.png")) {
		sf::err() << "Couldn't load SoundIcon\n";
		bool couldnt_load = true;
	}
	if (!icon_text.loadFromFile("SNElement Resources/TextIcon.png")) {
		sf::err() << "Couldn't load TextIcon\n";
		bool couldnt_load = true;
	}
	if (!icon_video.loadFromFile("SNElement Resources/VideoIcon.png")) {
		sf::err() << "Couldn't load VideoIcon\n";
		bool couldnt_load = true;
	}

	if (!radio_empty.loadFromFile("SNElement Resources/RadioButtonEmpty.png")) {
		sf::err() << "Couldn't load RadioEmptyIcon\n";
		bool couldnt_load = true;
	}
	if (!radio_full.loadFromFile("SNElement Resources/RadioButtonFull.png")) {
		sf::err() << "Couldn't load RadioFullIcon\n";
		bool couldnt_load = true;
	}

	if (couldnt_load) {
		sf::err() << "Application resources were not all loaded. Try repairing or reinstalling your application.\n";
	}

	main_window.create(sf::VideoMode(screen_width, screen_height), title);
	refresh_grid();
}

// Processing modifiers for global style values:
void fill(sf::Color color) {
	current_fill = color;
}
void fill(int fill) {
	current_fill = sf::Color(fill, fill, fill, 255);
}
void no_fill() {
	current_fill = sf::Color::Transparent;
}
void stroke(sf::Color color) {
	current_stroke = color;
}
void stroke(int stroke) {
	current_stroke = sf::Color(stroke, stroke, stroke, 255);
}
void stroke_weight(int stroke_weight) {
	current_stroke_weight = stroke_weight;
}

// Changes the title of the application.
void set_title(string str) {
	setup_window(displayW, displayH, str);
}
// Draws rectangle to buffer.
void rect(double x, double y, double w, double h) {
	sf::RectangleShape r(sf::Vector2f(w * sw, h * sh));
	r.setPosition(x * sw, y * sh);
	r.setFillColor(current_fill);
	r.setOutlineThickness(current_stroke_weight);
	r.setOutlineColor(current_stroke);
	main_window.draw(r);
}
// Draws rectangle with an alpha fill to buffer.
void rect(double x, double y, double w, double h, int alpha) {
	sf::RectangleShape r(sf::Vector2f(w * sw, h * sh));
	r.setPosition(x * sw, y * sh);
	r.setFillColor(sf::Color(current_fill.r, current_fill.g, current_fill.b, alpha));
	r.setOutlineThickness(current_stroke_weight);
	r.setOutlineColor(current_stroke);
	main_window.draw(r);
}
// Draws circle to buffer.
void circle(double x, double y, double d) {
	sf::CircleShape c(d / 2 * sw);
	c.setPosition(x * sw, y * sh);
	c.setFillColor(current_fill);
	c.setOutlineThickness(current_stroke_weight);
	c.setOutlineColor(current_stroke);
	main_window.draw(c);
}
// Draws circle with an alpha fill to buffer.
void circle(double x, double y, double d, int alpha) {
	sf::CircleShape c(d / 2 * sw);
	c.setPosition(x * sw, y * sh);
	c.setFillColor(sf::Color(current_fill.r, current_fill.g, current_fill.b, alpha));
	c.setOutlineThickness(current_stroke_weight);
	c.setOutlineColor(current_stroke);
	main_window.draw(c);
}
// Draws line using vertex shape to buffer.
class sfLine : public sf::Drawable {
public:
	sfLine(const sf::Vector2f& point1, const sf::Vector2f& point2)
		: fill(sf::Color::Yellow), thickness(1.f) {
		sf::Vector2f direction = point2 - point1;
		sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
		sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

		sf::Vector2f offset = (thickness / 2.f) * unitPerpendicular;

		vertices[0].position = point1 + offset;
		vertices[1].position = point2 + offset;
		vertices[2].position = point2 - offset;
		vertices[3].position = point1 - offset;

		for (int i = 0; i < 4; ++i) {
			vertices[i].color = fill;
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(vertices, 4, sf::Quads);
	}
	void setFillColor(sf::Color fill) {
		for (int i = 0; i < 4; ++i) {
			vertices[i].color = fill;
		}
	}

public:
	sf::Vertex vertices[4];
	float thickness;
	sf::Color fill;
};
void line(double x1, double y1, double x2, double y2) {
	sfLine line(sf::Vector2f(x1 * sw, y1 * sh), sf::Vector2f(x2 * sw, y2 * sh));
	line.setFillColor(current_fill);
	line.thickness = current_stroke_weight;
	main_window.draw(line);
}
// Returns grid based text width.
double text_width(string str, double h) {
	sf::Text text;

	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setString(str);
	text.setCharacterSize(h * sh);
	double text_w = text.getGlobalBounds().width / sw;
	return text_w;
}
// Draws text to buffer.
void text(string str, double x, double y, double h) {
	sf::Text text;
	// Text Style:
	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(current_fill);
	text.setString(str);
	text.setCharacterSize(h * sh);
	// Text Positioning:
	text.setPosition(sf::Vector2f(x * sw, y * sh));

	main_window.draw(text);
}
// Draws y centered text within a given x, y, h and text_h to buffer.
void y_centered_text(string str, double x, double y, double h, double text_h) {
	sf::Text text;
	// Text Style:
	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(current_fill);
	text.setString("l"); // Set string to l for consistent text height regardless of entered str
	text.setCharacterSize(text_h * sh);
	
	// Text Positioning:
	double centered_offset_y = ((h * sh) - text.getGlobalBounds().height) / 2;
	int centered_y = (y * sh) + centered_offset_y;
	text.setString(str);
	text.setOrigin(text.getGlobalBounds().left, text.getGlobalBounds().top);
	text.setPosition(sf::Vector2f(int(x * sw), centered_y));

	main_window.draw(text);
}
// Draws x and y centered text within a given x, y, w, h and text_h to buffer.
void all_centered_text(string str, double x, double y, double w, double h, double text_h) {
	sf::Text text;
	// Text Style:
	text.setFont(font);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(current_fill);
	text.setString("l"); // Set string to l for consistent text height regardless of entered strtext.setString(str);
	int smallest_s = (sh > sw) ? sw : sh;
	int text_s = (text_width(str, text_h)>(w-0.4)) ? smallest_s : sh;
	text.setCharacterSize(text_h * text_s);
	// Text Positioning:
	double centered_offset_y = ((h * sh) - text.getGlobalBounds().height) / 2;
	int centered_y = (y * sh) + centered_offset_y;
	text.setString(str);
	double centered_offset_x = ((w * sw) - (text.getGlobalBounds().width)) / 2;
	int centered_x = (x * sw) + centered_offset_x;
	text.setOrigin(text.getGlobalBounds().left, text.getGlobalBounds().top);
	text.setPosition(sf::Vector2f(centered_x, centered_y));

	main_window.draw(text);
}
// Fills buffer with sf::Color.
void background(sf::Color color) {
	main_window.clear(color);
}
// Fills buffer with rgb(255-0).
void background(int color) {
	main_window.clear(sf::Color(color, color, color, 255));
}
// Draws an sf::image object to buffer at default image size.
void image(sf::Image* img, double x, double y) {
	sf::Texture temp;
	sf::Sprite sprit;
	sprit.setPosition(sf::Vector2f(int(x * sw), int(y * sh)));
	temp.loadFromImage(*img);
	sprit.setTexture(temp);
	main_window.draw(sprit);
}
// Draws an sf::image object to buffer with given width and height.
// Images scale best by factors of two.
void image(sf::Image* img, double x, double y, int new_width, int new_height) {
	double scale_w = (float)(new_width * sw) / img->getSize().x;
	double scale_h = (float)(new_height * sh) / img->getSize().y;
	sf::Texture temp;
	sf::Sprite sprit;
	sprit.setPosition(sf::Vector2f(int(x * sw), int(y * sh)));
	temp.loadFromImage(*img);
	sprit.setTexture(temp);
	sprit.setScale(sf::Vector2f(scale_w, scale_h));
	main_window.draw(sprit);
}

// Displays the grid which processing functions are based on.
void dev_grid() {
	stroke(120);
	stroke_weight(1);
	no_fill();
	for (int x = 0; x < gridW + 1; x++) { // Note gridW is main display, the +1 is for partially displaying border
		for (int y = 0; y < gridH + 1; y++) {
			rect(x, y, 1, 1);
		}
	}
	stroke_weight(2);
}
// Plain background.
void gridless() {
	main_window.clear(sf::Color(32, 32, 32));
}
// Image background.
void background2() {
	main_window.clear(sf::Color(32, 32, 32));
	image(&bg2, 0, 0, 32, 18);
}
void background4() {
	main_window.clear(sf::Color(32, 32, 32));
	image(&bg4, 0, -2, 32, 24);
}

// ********************************************************************************************
// Group2: SNElement classes : SNElement, SNButton, SNLabel, SNContainer, SNCache, SNPageand SNApp class.

class SNElement {
	// Access specifier:
public:
	string type = "SNElement";
	string name;
	double x, y, w, h;
	void (*function)();

	// Default Constructor:
	SNElement() {
	}
	// Parameterized Constructor:
	SNElement(string name, double x, double y, double w, double h) {
		this->name = name;
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	// Methods:
	virtual void draw_element() {
		cout << " " << name << " (virtual draw func)." << x << "." << y << endl;
		fill(220);
		stroke(255);
		stroke_weight(2);
		rect(x, y, w, h, 25);
	}
};


class SNLabel : public SNElement {
	// Access specifier:
public:
	string str;
	double text_h;
	bool isCentered;

	// Default Constructor:
	SNLabel() {
	}
	// Parameterized
	SNLabel(string str, bool isCentered, double x, double y, double w, double h, double text_h)
		: SNElement(name, x, y, w, h) {
		this->type = "SNLabel";
		this->text_h = text_h;
		this->str = str;
		this->isCentered = isCentered;
	}

	void draw_element() { // Overloading virtual parent func.
		cout << " " << name << " (overloaded draw func)." << x << endl;
		fill(255);
		stroke(255);
		if (isCentered) {
			all_centered_text(str, x, y, w, h, text_h);
		}
		else {
			y_centered_text(str, x, y, h, text_h);
		}
	}
};


class SNButton : public SNElement {
	// Access specifier:
public:
	bool is_selected = false;
	bool is_centered = false;
	void (*function)();

	// Default Constructor:
	SNButton() {
		this->type = "SNButton";
	}
	// Parameterized Constructor:
	SNButton(string name, double x, double y, double w, double h, void (*function)())
		: SNElement(name, x, y, w, h) {
		this->type = "SNButton";
		this->function = function;
	}
	SNButton(string name, double x, double y, double w, double h, bool is_centered, void (*function)())
		: SNElement(name, x, y, w, h) {
		this->type = "SNButton";
		this->function = function;
		this->is_centered = is_centered;
	}

	// Methods:
	void draw_element() {
		cout << " " << name << " (overloaded draw func)." << x << "." << y << endl;
		fill(220);
		if (is_selected) {
			stroke(sf::Color(20, 140, 150));
		}
		else {
			stroke(255);
		}
		stroke_weight(2);
		rect(x, y, w, h, 25);
		fill(255);
		if (is_centered) {
			all_centered_text(name, x, y, w, h, h * .6);
		}
		else {
			y_centered_text(name, x + 0.2, y, h, h * .6);
		}
	}
};


class SNButton_in_set : public SNElement { // Useful for when button position in a set is relevant.
	// Access specifier:
public:
	bool is_selected = false;
	int button_position;
	void (*function)(int);

	// Default Constructor:
	SNButton_in_set() {
		this->type = "SNButton_in_set";
	}
	// Parameterized Constructor:
	SNButton_in_set(string name, double x, double y, double w, double h, void (*function)(int), int button_position)
		: SNElement(name, x, y, w, h) {
		this->type = "SNButton_in_set";
		this->function = function;
		this->button_position = button_position;
	}

	void draw_element() {
		cout << " " << name << " (overloaded draw func)." << x << "." << y << endl;
		fill(220);
		if (is_selected) {
			stroke(sf::Color(20, 140, 150));
		}
		else {
			stroke(255);
		}
		stroke_weight(2);
		rect(x, y, w, h, 25);
		fill(255);
		y_centered_text(name, x + 0.2, y, h, h * 0.6);
	}
};


class SNRadio_Button : public SNButton {
	// Access specififer:
public:
	bool is_selected = false;
	SNRadio_Button** current_rb;

	// Deafult Constructor:
	SNRadio_Button() {
	}
	// Parametereized Constructor:
	SNRadio_Button(string name, double x, double y, double w, double h, void (*function)(), SNRadio_Button** current_rb)
		: SNButton(name, x, y, w, h, function) {
		this->type = "SNRadio_Button";
		this->current_rb = current_rb;
	}

	// Methods:
	void draw_element() {
		cout << " " << name << " (overloaded draw func)." << x << "." << y << endl;
		if (is_selected) {
			image(&radio_full, x, y, 1, 1);
		}
		else {
			image(&radio_empty, x, y, 1, 1);
		}
		fill(255);
		stroke_weight(2);
		y_centered_text(name, x + 1.2, y, h, 0.6);
	}
	void radio_switch() {
		SNRadio_Button* t = *current_rb;
		if (t != NULL) {
			t->is_selected = false;
			this->is_selected = true;
			*current_rb = this;
		}
		else {
			cout << "No initial radio button set" << endl;
		}
		function();
	}
};


class SNContainer : public SNElement {
	// Access specifier:
public:
	vector<SNElement*> elements;
	string title;

	// Default Constructor:
	SNContainer() {
	}
	// Parameterized Constructor:
	SNContainer(string name, double x, double y, double w, double h, vector<SNElement*> elements, string title)
		: SNElement(name, x, y, w, h) {
		this->elements = elements;
		this->title = title;
	}

	void draw_element() { // Overloading virtual parent func.
		cout << " " << name << " (container draw func)." << x << "." << y << endl;
		no_fill();
		stroke(220);
		stroke_weight(2);
		double title_w = ceil(text_width(title, 0.7)); // title
		rect(x + title_w, y + .5, w - title_w, 0); // title line -----------------------------
		fill(255);
		all_centered_text(title, x, y, title_w, 1, 0.6);
		for (int i = 0; i < elements.size(); i++) {
			elements[i]->draw_element();
		}
	}
};


int dice_probabilities[] = { 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1 };
int roll2 = 2; int roll3 = 4; int roll4 = 6; int roll5 = 8; int roll6 = 10; int roll7 = 12; int roll8 = 10;
int roll9 = 8; int roll10 = 6; int roll11 = 4; int roll12 = 2;
int* dice_datas[] = { &roll2, &roll3, &roll4, &roll5, &roll6, &roll7, &roll8, &roll9, &roll10, &roll11, &roll12 };


int num_rolled2 = 0; int num_rolled3 = 0; int num_rolled4 = 0; int num_rolled5 = 0; int num_rolled6 = 0;
int num_rolled7 = 0; int num_rolled8 = 0; int num_rolled9 = 0; int num_rolled10 = 0; int num_rolled11 = 0;
int num_rolled12 = 0;
int* nums_rolleds[] = { &num_rolled2, &num_rolled3, &num_rolled4, &num_rolled5, &num_rolled6, &num_rolled7, &num_rolled8,
&num_rolled9,&num_rolled10,&num_rolled11,&num_rolled12 };

vector<int> recorded_rolls = {};
class statistics_bar : public SNButton {
	// Access specifier:
public:
	int* dice_data;
	int* dice_rolled;
	int display_val;
	bool is_top_bar = true;
	double percent_chance;

	// Default constructor:
	statistics_bar() {
	}
	// Parameterized constructor:
	statistics_bar(string name, double x, double y, double w, double h, void (*function)(), bool is_top_bar, int* dice_data, int* dice_rolled)
		: SNButton(name, x, y, w, h, function) {
		this->type = "statistics_bar";
		this->is_top_bar = is_top_bar;
		this->dice_data = dice_data;
		this->dice_rolled = dice_rolled;
		if (is_top_bar) {
			display_val = *dice_data - *dice_rolled;
		}
		else {
			display_val = *dice_rolled;
		}
	}

	void update_data() {
		if (is_top_bar) {
			display_val = *dice_data - *dice_rolled;
		}
		else {
			display_val = *dice_rolled;
		}
		if (display_val >= 2 || display_val == 0) {
			h = (double(display_val) / 2) + 1;
		}
		else {
			h = 1 + 1;
		}
		int sum = 0;
		for (int i = 0; i < 11; i++) {
			sum += *dice_datas[i] - *nums_rolleds[i];
		}
		percent_chance = (double(display_val)) / double(sum) * 100;
		
	}
	void draw_element() {
		cout << " Dice Number " << name << " (overloaded draw func)." << x << "." << y << endl;
		update_data();
		fill(220);
		
		if (is_top_bar) {
			stroke_weight(1);
			rect(x, y + 1, w, h - 1, 25);
			fill(255);
			stroke_weight(2);
			all_centered_text(name, x, y, w, 1, 0.6);
			all_centered_text(to_string(display_val), x, y + 1, w, 1, 0.6);
			if (percent_chance > 0) {
				string display_percent = to_string(percent_chance);
				if (percent_chance / 10 > 1) {
					display_percent = display_percent.substr(0, 4);
				}else{
					display_percent = display_percent.substr(0, 3);
				}
				all_centered_text(display_percent + "%", x, y + h, w, 1, 0.6);
			}
		}
		else {
			stroke_weight(1);
			rect(x, y-h, w, h - 1, 25);
			fill(255);
			stroke_weight(2);
			all_centered_text(name, x, y -1, w, 1, 0.6);
			all_centered_text(to_string(display_val), x, y-2 , w, 1, 0.6);
		}
	}
	void data_change() {
		if (is_top_bar && (*dice_data-*dice_rolled != 0)) {
			*dice_rolled = *dice_rolled + 1;
			display_val = *dice_data - *dice_rolled;
			recorded_rolls.push_back(std::stoi(name));
		}
		else if(!is_top_bar && (*dice_rolled !=0)) {
			*dice_rolled = *dice_rolled - 1;
			display_val = *dice_rolled;
			for (int i = recorded_rolls.size() - 1; i >= 0; i--) {
				if (recorded_rolls[i] == std::stoi(name)) {
					recorded_rolls.erase(recorded_rolls.begin()+i);
					break;
				}
			}
		}
		update_data();
		function();
	}
};


class cache { // For storing loop created objects.
// Access specifier:
public:
	vector<SNButton> buttons = {};
	vector<SNButton_in_set> buttons_in_set = {};
	vector<SNElement> elements = {};
	vector<SNLabel> labels = {};
	vector<SNContainer> containers = {};
	vector<statistics_bar> statistics_bars = {};
	
	// Default constructor:
	cache() {
	}

	// Methods:
	void clear_all(vector<SNElement*>* page_elements) {
		page_elements->clear();
		buttons.clear();
		buttons_in_set.clear();
		elements.clear();
		labels.clear();
		containers.clear();
		statistics_bars.clear();
	}
};

bool uses_dev_grid = false;
class SNPage {
	// Access specifier:
public:
	string name;
	vector<SNElement*> elements;
	vector<SNElement*> post_elements;
	void (*draw_func)();
	void (*page_setup)();

	// Default constructor:
	SNPage() {
	}
	// Parameterized Constructor:
	SNPage(string name, vector<SNElement*> elements, void (*page_setup)(), void (*draw_func)()) {
		this->name = name;
		this->elements = elements;
		this->page_setup = page_setup;
		this->draw_func = draw_func;
	}

	void draw_page() {
		main_window.clear();
		// Basic background
		if (uses_dev_grid) {
			dev_grid();
		}
		else {
			gridless();
		}
		cout << "Drawing " << name << endl;
		draw_func();
		for (int i = 0; i < elements.size(); i++) {
			elements[i]->draw_element();
		}
		for (int i = 0; i < post_elements.size(); i++) {
			post_elements[i]->draw_element();
		}
		cout << endl;
		main_window.display();
	}

	void check_buttons(double mouse_x, double mouse_y) {
		double grid_x = mouse_x / sw;
		double grid_y = mouse_y / sh;
		for (int i = 0; i < elements.size(); i++) {
			SNElement* e = elements[i];
			if (e->type == "SNButton") {
				if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
					SNButton* button_ptr = dynamic_cast<SNButton*>(e);
					button_ptr->function();
					cout << e->name << " has been pressed." << endl;
				}
			}
			if (e->type == "SNRadio_Button") {
				if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
					SNRadio_Button* button_ptr = dynamic_cast<SNRadio_Button*>(e);
					button_ptr->radio_switch();
					cout << e->name << " has been pressed." << endl;
				}
			}
			if (e->type == "SNButton_in_set") {
				if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
					SNButton_in_set* button_ptr = dynamic_cast<SNButton_in_set*>(e);
					button_ptr->function(button_ptr->button_position);
				}
			}
			if (e->type == "statistics_bar") {
				statistics_bar* button_ptr = dynamic_cast<statistics_bar*>(e);
				if (button_ptr->is_top_bar) {
					if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
						button_ptr->data_change();
						cout << e->name << " has been pressed." << endl;
					}
				}
				else {
					if (e->x < grid_x && grid_x < e->x + e->w && e->y - e->h < grid_y && grid_y < e->y - e->h + e->h) {
						button_ptr->data_change();
						cout << e->name << " has been pressed." << endl;
					}
				}
			}
		}
		for (int i = 0; i < post_elements.size(); i++) {
			SNElement* e = post_elements[i];
			if (e->type == "SNButton") {
				if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
					SNButton* button_ptr = dynamic_cast<SNButton*>(e);
					button_ptr->function();
					cout << e->name << " has been pressed." << endl;
				}
			}
			if (e->type == "SNRadio_Button") {
				if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
					SNRadio_Button* button_ptr = dynamic_cast<SNRadio_Button*>(e);
					button_ptr->radio_switch();
					cout << e->name << " has been pressed." << endl;
				}
			}
			if (e->type == "SNButton_in_set") {
				if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
					SNButton_in_set* button_ptr = dynamic_cast<SNButton_in_set*>(e);
					button_ptr->function(button_ptr->button_position);
					cout << e->name << " has been pressed." << endl;
				}
			}
			if (e->type == "statistics_bar") {
				statistics_bar* button_ptr = dynamic_cast<statistics_bar*>(e);
				if (button_ptr->is_top_bar) {
					if (e->x < grid_x && grid_x < e->x + e->w && e->y < grid_y && grid_y < e->y + e->h) {
						button_ptr->data_change();
						cout << e->name << " has been pressed." << endl;
					}
				}
				else {
					if (e->x < grid_x && grid_x < e->x + e->w && e->y-e->h < grid_y && grid_y < e->y-e->h + e->h) {
						button_ptr->data_change();
						cout << e->name << " has been pressed." << endl;
					}
				}
			}
		}
	}
};


class SNApp {
// Access specifier:
public:
	vector<SNPage*> pages;
	SNPage* current_page;
	
	// Default constructor:
	SNApp() {
	}

	// Methods:
	void add_page(SNPage* new_page) {
		if (pages.size() == 0) {
			current_page = new_page;
		}
		pages.push_back(new_page);
	}
	void activate_page(SNPage* p) {
		p->page_setup();
		p->draw_page();
		current_page = p;
	}
	void refresh_page() {
		current_page->page_setup();
		current_page->draw_page();
	}
};


// ********************************************************************************************
// Group3: SNElement navigation page creation.
SNApp my_app;
/*	SUB Groups
*	GroupA: SNElement declarations
*	GroupB: SNPage declarations(SNElements are in pages)
*
*	GroupC: SNElements' function initializations
*	GroupD: SNEPages' function initializations */


// GroupA: SNElement declarations
void function_temp(){};
void function_open_page(int pos);
void function_rb_dev();
void function_rb_plain();

SNLabel l_SNEM_title("SNElements Main:", false, 1, 0, 6, 2, text_width("SNElements Main", 2));
SNLabel l_sidebar_title("View Options:", true, 25, 0.1, 7, 1, .6);
SNRadio_Button* SNEM_current_rb;
SNRadio_Button rb_dev("Developer Grid", 25, 2, 7, 1, &function_rb_dev, &SNEM_current_rb);
SNRadio_Button rb_plain("No Grid", 25, 3, 7, 1, &function_rb_plain, &SNEM_current_rb);

vector<SNElement*> SNEM_elements = {
	&l_SNEM_title,
	&l_sidebar_title,
	&rb_dev,
	&rb_plain
};

// GroupB: SNPage declarations(SNElements are in pages)
void setup_SNElement_main();
void draw_SNElement_main();

cache SNEM_page_cache = cache();
SNPage SNEM("SNElements Main", SNEM_elements, &setup_SNElement_main, &draw_SNElement_main);


// GroupC: SNElements' function initializations
void function_open_page(int pos) {
	if (my_app.pages.size() > pos) {
		my_app.activate_page(my_app.pages[pos]);
	}
}
void function_rb_dev() {
	uses_dev_grid = true;
	my_app.refresh_page();
}
void function_rb_plain() {
	uses_dev_grid = false;
	my_app.refresh_page();
}


// GroupD: SNEPages' function initializations */
void setup_SNElement_main() { // Creates new buttons to navigate pages added to my_app
	SNEM_page_cache.clear_all(&SNEM.post_elements);
	SNButton_in_set temp_button;
	for (int i = 0; i < my_app.pages.size(); i++) {
		temp_button.~SNButton_in_set();
		new(&temp_button) SNButton_in_set(my_app.pages[i]->name, 1, 2 + i * 2, text_width(my_app.pages[i]->name, 1 * 0.6) + 1, 1, &function_open_page, i);
		SNEM_page_cache.buttons_in_set.push_back(temp_button);
	}
	for (int i = 0; i < SNEM_page_cache.buttons_in_set.size(); i++) {
		SNEM.post_elements.push_back(&SNEM_page_cache.buttons_in_set[i]);
	}
}
void draw_SNElement_main() {
	fill(220);
	stroke(220);
	stroke_weight(4);
	int sidebar_width = 7;
	rect(gridW - sidebar_width, 0, sidebar_width + 1, gridH + 1, 25);
}