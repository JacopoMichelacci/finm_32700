## Phase 2: Momentum-Based Smart Order Client

For the strategy that we implemented for this phase we chose to follow closely the specs instructions for modifying the RecieveAndRespond function. In terms of our design decisions for parsing the input we followed the spec and used stoi and stoif. For storing the previous 3 values we used the double ended qeue priceHistory and opted to include the most recent price in the 0th index and move the oldest price out of the end. 

Additionally we implemented the momentum aspect of the platform if we see momentum up or down to hit the server using the priceHistory, previous 3 prices. After making these implementations we ensured that our implementation worked as intended, we filmed the video indicating that the client and server worked as intended. 