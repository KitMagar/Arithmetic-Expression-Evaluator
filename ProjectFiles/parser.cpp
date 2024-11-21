//parser.cpp
//Phoenix Brehm and Kit Magar

/*
Purpose: To take in an input from the lexer in the form of a linked list and output a binary tree, one with the order of operations happening in post-order. This tree will be passed into the evaluator for it to evaluate the tree in this order. The parser will also handle errors like incorrect parenthesis use, nonsensical orderings like 3+*4, and the distriubutive property.

By post order the intention is to go as far down as possible, then once you have two numbers go up go to the common parent and perform the operation, continue until the root is missing.
*/