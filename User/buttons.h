#pragma once

const int buttonCount = 6;
const int buttonPins[buttonCount] = {0, 3, 14, 18, 19, 15};
GPIO_TypeDef *buttonPorts[buttonCount] = {GPIOC, GPIOC, GPIOC, GPIOC, GPIOC, GPIOC};
int buttonChanged[buttonCount];
int buttonRepeat[buttonCount];
int button[buttonCount];
int buttonPressedCount[buttonCount];

const int  BUTTON_REPEAT_DELAY = 300;
const int  BUTTON_REPEAT_DELAY2 = 100;
const int  BUTTON_DEBOUNCE_DELAY = 0;

enum Button
{
    A = 0,
    B = 1,
    UP = 2,
    DOWN = 3,
    LEFT = 4,
    RIGHT = 5
};

void initButtons()
{
    for(int i = 0; i < 6; i++)
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};
        GPIO_InitStructure.GPIO_Pin = 1 << buttonPins[i];//GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(buttonPorts[i], &GPIO_InitStructure);
        buttonChanged[i] = 0;
        buttonRepeat[i] = 0;
        buttonPressedCount[i] = 0;
        button[i] = 0;
    }
}

int readButton(int i)
{
    return GPIO_ReadInputDataBit(buttonPorts[i], 1 << buttonPins[i]) ? 0 : 1;
}

int buttonBits()
{
    int b = 0;
    for(int i = 0; i < 6; i++)
        b |= readButton(i) << i;
    return b;
}

void processButtons(int dt = 1)
{
    for(int i = 0; i < 6; i++)
    {
        int b = readButton(i);
        if(b == button[i])  //button same
        {
            buttonChanged[i] += dt;
            if(b)
                buttonRepeat[i] -= dt;
        }
        else
        {
            buttonChanged[i] = 0;
            if(b)
                buttonRepeat[i] = BUTTON_REPEAT_DELAY;
            if(!b && buttonChanged[i] >= BUTTON_DEBOUNCE_DELAY)
            {
                buttonPressedCount[i]++;
            }
        }
        button[i] = b;
        if(button[i])
        {
            if(buttonRepeat[i] <= 0)
            {
                buttonRepeat[i] = BUTTON_REPEAT_DELAY2;
                buttonPressedCount[i]++;
            }
        }
    }
}

bool buttonDown(int b)
{
    return (button[b] > 0) && (buttonChanged[b] >= BUTTON_DEBOUNCE_DELAY);
}

int buttonPressed(int b)
{
    //if(button[b]) return 1;
    //return 0;
    int i = buttonPressedCount[b];
    buttonPressedCount[b] = 0;
    return i;
}
