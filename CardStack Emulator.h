#pragma once
#include <SFML/Graphics.hpp>
#include "SNElement.h"


/*	Group0: Custom CardStack class
*	Group1: SNElement declarations
*	Group2: SNPage declarations(SNElements are in pages)
*
*	Group3: SNElements' function initializations
*	Group4: SNEPages' function initializations */


// *******************************************************************************************************
// Group1: SNElement declarations
void function_data_change();
void setup_helper_reset();
void function_clear();

SNLabel l_remaining_cardstack("Maximum cards left", true, 11, 0, 10, 1, 0.8);
SNLabel l_dice_statistics("Dice Statistics", true, 11, 17, 10, 1, 0.8);
SNButton b_reset("Reset Stack", 9.5, 8.5, 5, 1, true, &setup_helper_reset);
SNButton b_clear("Clear Rolls", 17.5, 8.5, 5, 1, true, &function_clear);

vector<SNElement*> cardstack_elements = {
	&l_remaining_cardstack,
	&l_dice_statistics,
	&b_reset,
	&b_clear
};

// *******************************************************************************************************
// Group2: SNPage declarations(SNElements are in pages)
void setup_cardstack();
void draw_cardstack();

cache cardstack_cache = cache();
SNPage cardstack_page("Cardstack Page", cardstack_elements, &setup_cardstack, &draw_cardstack);
// *******************************************************************************************************
// Group3: SNElements' function initializations
void function_data_change() {
	my_app.current_page->draw_page();
}
void function_clear() {
	recorded_rolls.clear();
	my_app.current_page->draw_page();
}

// *******************************************************************************************************
// Group4: SNEPages' function initializations
void setup_helper_reset() {
	for (int i = 0; i < 11; i++) {
		(*nums_rolleds[i]) = 0;
	}
	my_app.activate_page(&cardstack_page);
}
void setup_cardstack() {
	cardstack_cache.clear_all(&cardstack_page.post_elements);
	statistics_bar temp_bar;
	for (int i = 0; i < 11; i++) {
		temp_bar.~statistics_bar();
		new(&temp_bar) statistics_bar(to_string(2 + i), 2.5 + (i * 2.5), 1, 2, dice_probabilities[i]+1, &function_data_change, true, dice_datas[i], nums_rolleds[i]);
		cardstack_cache.statistics_bars.push_back(temp_bar);
	}
	for (int i = 0; i < 11; i++) {
		temp_bar.~statistics_bar();
		new(&temp_bar) statistics_bar(to_string(2 + i), 2.5 + (i * 2.5), 17, 2, dice_probabilities[i] + 1, &function_data_change, false, dice_datas[i], nums_rolleds[i]);
		cardstack_cache.statistics_bars.push_back(temp_bar);
	}
	for (int i = 0; i < cardstack_cache.statistics_bars.size(); i++) {
		cardstack_page.post_elements.push_back(&cardstack_cache.statistics_bars[i]);
	}
}
void draw_cardstack() {
	stroke_weight(1);
	fill(220);
	stroke(255);
	// Top line
	rect(1, 2, 30, 0);
	// Bottum line
	rect(1, 16, 30, 0);
	// Sidebar
	rect(30, 5, 2, 9,25);

	// Right side dice recorder
	int x = 0;
	if (recorded_rolls.size() > 9) {
		x = recorded_rolls.size() - 9;
	}
	for (int i = x; i < recorded_rolls.size(); i++) {
		int temp_y = i-x;
		fill(255);
		all_centered_text(to_string(recorded_rolls[i]), 30.45, temp_y+5, 1, 1, 0.6);
	}

	// Roll Wiper at roll 36
	if (recorded_rolls.size() == 36) {
		recorded_rolls.push_back(00);
		for (int i = 0; i < 11; i++) {
			(*nums_rolleds[i]) = 0;
		}
	}

	// Top Right stack indicator
	stroke_weight(2);
	int sum = 0;
	for (int i = 0; i < 11; i++) {
		sum += *nums_rolleds[i];
	}
	string num_rolls = to_string(sum);
	y_centered_text(num_rolls + "/36", 30, 0.1, 2, 0.6);
}