# balancedCentrifugeProblem_C

## Description

Implementation of The Balanced Centrifuge Problem using the the C language. <br />

This is one of the, probably many, ways to simulate this mathematical problem.

## The Problem:

A centrifuge  is a laboratory device which spins liquid samples at high speed in order to separate them based on density. It’s very important to balance a centrifuge before operating it - not doing it by using, for example, just a tube on only one side, the rotating mass will not be balanced causing the centrifuge to shake when rotating and may even damage the centrifuge or the tube. A tube on the opposite side is used to balance the mass for smooth operation. <br />

So, a centrifuge is balanced if the center of mass of the collection of test tubes coincides with the center of mass of the centrifuge itself. <br />

The problem is - given the number of holes in the centrifuge - for which different numbers of test tubes can you obtain a balanced-configuration?  

## The Solution:

(1) Number of Test Tubes.<br />
(2) Number of Empty Spots in the Centrifuge.<br />
(3) Number of Holes in the Centrifuge.<br />

You can balance the centrifuge if and only if both (1) and (2) can be written as sums of prime factors of (3).



## Example 1:

For the case of a centrifuge with 12-holes. <br />

The prime factors of 12 are 2 and 3. <br />

You can have a balanced-configuration for 2, 3, 4, 5, 6, 7, 8, 9, 10, 12 test tubes in a 12-hole centrifuge. <br />

*Notice that, for example, for 5 test tubes, you have<br />
(1) Number of Test Tubes = 5;<br />
(2) Number of Empty Holes = 12 - 5 = 7.<br />

Being that the prime factors of 12 are 2 and 3, you can easily see that you can write (1) and (2) as sums of those prime factors.<br />
(1) 5 = 2 + 3;<br />
(2) 7 = 2 + 2 + 3;<br />

So, you can have a 5 tubes balanced in a 12-hole centrifuge.

## Example 2:

In the other hand, it's easy to understand that if you have 11 test tubes you will never be able to have a balanced-configuration.<br />

(1) Number of Test Tubes = 11.<br />
(2) Number of Empty Holes = 12 - 11 = 1.<br />

You can't write (1) or (2) as sums of the prime factors of 12 (which are, again, 2 and 3).
