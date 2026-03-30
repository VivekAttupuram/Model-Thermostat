#ifndef SPI_H
#define SPI_H

// Pins for SPIx 
#define USESPI1 // define to USESPI1/USESPI2 depending on what set you are using

// definitons for signaling high and low
#define LOW 0
#define HIGH 1
#define SPI_PPRE 0b11
#define SPI_SPRE 0b111

void config_spi();

#endif