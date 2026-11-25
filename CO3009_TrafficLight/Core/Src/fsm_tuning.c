/*
 * fsm_tuning.c
 *
 *  Created on: Nov 4, 2026
 *      Author: Admin
 */

#include "fsm_tuning.h"

void fsm_tuning_init(void)
{
    tuning_select = TUNE_RED;
    temp_red = time_red;
    temp_amber = time_amber;
    temp_green = time_green;
    save_notification = NOTIF_NONE;
    traffic_off_all();
    setTimer(TIMER_BLINK, 250);
}

void fsm_tuning_run(void)
{
    if (system_mode != MODE_TUNING)
    {
        return;
    }

    if (isTimerExpired(TIMER_BLINK))
    {
        if (tuning_select == TUNE_RED)
        {
            traffic_toggle(1, LIGHT_RED);
            traffic_toggle(2, LIGHT_RED);
        }
        else if (tuning_select == TUNE_AMBER)
        {
            traffic_toggle(1, LIGHT_AMBER);
            traffic_toggle(2, LIGHT_AMBER);
        }
        else if (tuning_select == TUNE_GREEN)
        {
            traffic_toggle(1, LIGHT_GREEN);
            traffic_toggle(2, LIGHT_GREEN);
        }
        setTimer(TIMER_BLINK, 250);
    }

    if (button_is_pressed(BTN_INDEX_2))
    {
        save_notification = NOTIF_NONE;

        if (tuning_select == TUNE_RED)
            tuning_select = TUNE_AMBER;
        else if (tuning_select == TUNE_AMBER)
            tuning_select = TUNE_GREEN;
        else
            tuning_select = TUNE_RED;

        traffic_off_all();
        setTimer(TIMER_BLINK, 250);
    }

    if (button_is_pressed(BTN_INDEX_3) || button_is_held(BTN_INDEX_3))
    {
        save_notification = NOTIF_NONE;

        if (tuning_select == TUNE_RED)
        {
            if (temp_red < 99) temp_red++; else temp_red = 2;
        }
        else if (tuning_select == TUNE_AMBER)
        {
            if (temp_amber < 99) temp_amber++; else temp_amber = 1;
        }
        else if (tuning_select == TUNE_GREEN)
        {
            if (temp_green < 99) temp_green++; else temp_green = 1;
        }
    }

    if (button_is_pressed(BTN_INDEX_4) || button_is_held(BTN_INDEX_4))
    {
        save_notification = NOTIF_NONE;

        if (tuning_select == TUNE_RED)
        {
            if (temp_red > 2) temp_red--; else temp_red = 99;
        }
        else if (tuning_select == TUNE_AMBER)
        {
            if (temp_amber > 1) temp_amber--; else temp_amber = 99;
        }
        else if (tuning_select == TUNE_GREEN)
        {
            if (temp_green > 1) temp_green--; else temp_green = 99;
        }
    }

    if (button_is_pressed(BTN_INDEX_USER))
    {
        if (temp_red == (temp_amber + temp_green))
        {
            save_notification = NOTIF_SAVED;
        }
        else if(tuning_select == TUNE_RED)
        {

        	if(temp_red - temp_amber >= 1)
        		temp_green = temp_red - temp_amber;
        	else
        	{
        		temp_green = 1;
        		temp_amber = temp_red - temp_green;
        	}
        	save_notification = NOTIF_SYNCED;
        }
        else if(tuning_select == TUNE_AMBER || tuning_select == TUNE_GREEN)
        {
        	temp_red = temp_amber + temp_green;
        	save_notification = NOTIF_SYNCED;
        }
        else
        {
            temp_red = temp_amber + temp_green;
            save_notification = NOTIF_SYNCED;
        }



        time_red = temp_red;
        time_amber = temp_amber;
        time_green = temp_green;

        setTimer(TIMER_TIMEOUT, 1000);
    }

    if (save_notification != NOTIF_NONE && isTimerExpired(TIMER_TIMEOUT))
    {
        save_notification = NOTIF_NONE;
    }

    if (button_is_pressed(BTN_INDEX_1))
    {
        save_notification = NOTIF_NONE;

        if (time_red != (time_amber + time_green))
        {
            time_red = time_amber + time_green;
        }

        system_mode = MODE_AUTO;
        fsm_automatic_init();
    }
}
