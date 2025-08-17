#include "MGPIO_int.h"


void MGPIO_vSetMode(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8Mode){

    case(A_u8PortID) {
        case GPIOA:
            GPIOA->MODER &= ~(0x3U << (A_u8PinNum * 2));
            GPIOA->MODER |= (A_u8Mode << (A_u8PinNum * 2));
            break;
        case GPIOB:
            GPIOB->MODER &= ~(0x3U << (A_u8PinNum * 2));
            GPIOB->MODER |= (A_u8Mode << (A_u8PinNum * 2));
            break;
        case GPIOC:
            GPIOC->MODER &= ~(0x3U << (A_u8PinNum * 2));
            GPIOC->MODER |= (A_u8Mode << (A_u8PinNum * 2));
            break;
    }
}

void MGPIO_vSetOutputType(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8OutputType){

    if(A_u8OutputType == PUSHPULL)
    
    else if(A_u8OutputType == OPENDRAIN)
    {

    }
    switch(A_u8PortID) {
        case GPIOA:
            GPIOA->OTYPER &= ~(0x1U << A_u8PinNum);
            GPIOA->OTYPER |= (A_u8OutputType << A_u8PinNum);
            break;
        case GPIOB:
            GPIOB->OTYPER &= ~(0x1U << A_u8PinNum);
            GPIOB->OTYPER |= (A_u8OutputType << A_u8PinNum);
            break;
        case GPIOC:
            GPIOC->OTYPER &= ~(0x1U << A_u8PinNum);
            GPIOC->OTYPER |= (A_u8OutputType << A_u8PinNum);
            break;
    }
}

void MGPIO_vOutputSpeed(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8SOutputSpeed){

    switch(A_u8PortID) {
        case GPIOA:
            GPIOA->OSPEEDR &= ~(0x3U << (A_u8PinNum * 2));
            GPIOA->OSPEEDR |= (A_u8SOutputSpeed << (A_u8PinNum * 2));
            break;
        case GPIOB:
            GPIOB->OSPEEDR &= ~(0x3U << (A_u8PinNum * 2));
            GPIOB->OSPEEDR |= (A_u8SOutputSpeed << (A_u8PinNum * 2));
            break;
        case GPIOC:
            GPIOC->OSPEEDR &= ~(0x3U << (A_u8PinNum * 2));
            GPIOC->OSPEEDR |= (A_u8SOutputSpeed << (A_u8PinNum * 2));
            break;
    }
}

void MGPIO_vSetPushPull(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8PushPull){

    switch(A_u8PortID) {
        case GPIOA:
            CLR_BIT(GPIOA->OTYPER, A_u8PinNum);
            GPIOA->OTYPER |= (A_u8PushPull << A_u8PinNum);
            break;
        case GPIOB:
            CLR_BIT(GPIOB->OTYPER, A_u8PinNum);
            GPIOB->OTYPER |= (A_u8PushPull << A_u8PinNum);
            break;
        case GPIOC:
            CLR_BIT(GPIOC->OTYPER, A_u8PinNum);
            GPIOC->OTYPER |= (A_u8PushPull << A_u8PinNum);
            break;
    }
}

void MGPIO_vSetPinValue(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8Value){

    if (A_u8Value == GPIO_HIGH) {
        switch(A_u8PortID) {
            case GPIOA:
                SET_BIT(GPIOA->ODR, A_u8PinNum);
                break;
            case GPIOB:
                SET_BIT(GPIOB->ODR, A_u8PinNum);
                break;
            case GPIOC:
                SET_BIT(GPIOC->ODR, A_u8PinNum);
                break;
        }
    } else if (A_u8Value == GPIO_LOW) {
        switch(A_u8PortID) {
            case GPIOA:
                CLR_BIT(GPIOA->ODR, A_u8PinNum);
                break;
            case GPIOB:
                CLR_BIT(GPIOB->ODR, A_u8PinNum);
                break;
            case GPIOC:
                CLR_BIT(GPIOC->ODR, A_u8PinNum);
                break;
        }
    }
}

u8 MGPIO_u8GetPinValue(u8 A_u8PortID, u8 A_u8PinNum){

    switch(A_u8PortID) {
            case GPIOA:
                GET_BIT(GPIOA->IDR, A_u8PinNum);
                break;
            case GPIOB:
                GET_BIT(GPIOB->IDR, A_u8PinNum);
                break;
            case GPIOC:
                GET_BIT(GPIOC->IDR, A_u8PinNum);
                break;
        }
}

void MGPIO_vSetAlternateFunction(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8AlternateFunction){

}