/**
  Parsing Header File

  File Name:
    parse.h

  Summary:
    This is the header file for the parse.c file

  Author:
    D.Bachmann
  
  Date:
    11.05.2020
  
  Revision:
    1.0
*/

#ifndef PARSE_H
#define	PARSE_H

/*
  Section: Parsing APIs
*/

/**
  @Summary
    Parses the UART Input Data

  @Description
    This function parses the data from the UART module and saves the parameter
    in their corresponding variables

  @Preconditions
    None

  @Param
    None

  @Returns
    None
 
*/
void Parse_Data();

#endif	/* PARSE_H */
/**
 End of File
*/

