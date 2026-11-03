#pragma once

// grab a full line

// create a variable to store final variable (substring?)
// char previousChar
// int quoteCount
// bool finishedWithSubstring

// loop through each character in the line and while finishedWithSubstring is false. int curChar = line.get()

// if curChar is a quote, increment quoteCount
// if curChar is a comma, then if quoteCount is 0 OR if (previousChar is a quote AND if quoteCount % 2) == 0, then set finishedWithSubstring true
// after all that checking, set previousChar to curChar, then append previousChar to substring

// restart loop for nextChar



// THIS READS A SINGLE COLUMN OF CSV
// PARTIALLY PSEUDOCODE

// string substring
// char previousChar
// int quoteCount
// bool finishedWithSubstring
//
// for (int curChar; finishedWithSubstring == false && (curChar == line.getNextChar()) != endOfFile;)
// {
//      if (curChar == '"')
//      {
//          ++quoteCount;
//          break;
//      }
//      if (curChar == ',')
//      {
//          if (quoteCount == 0 || (previousChar == '"'  && (quoteCount % 2) == 0))
//          {
//              finishedWithSubstring = true;
//          }
//          break;
//      }
//      previousChar = curChar;
//      substring.append(previousChar);
// }
// return substring;
