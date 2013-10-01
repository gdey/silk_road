//
//  SRGM.m
//  Silkroad
//
//  Created by Jason Koo on 9/10/13.
//  Copyright (c) 2013 SilkRoad. All rights reserved.
//

#import "SRGM.h"

@implementation SRGM

#pragma mark - PRE GAME
- (void) startUp{
    if (![self areLoggedIn])    {  [self login];}
    if ([self wasInvited])      {  [self startInvitedGame];}
    else                        {  [self selectGame];}
}

- (BOOL) areLoggedIn{
    // TODO: Actual login code
    return NO;
}

- (void) login{
   // Handle login interface
}

- (BOOL) wasInvited{
    // Handle opening app from a game kit invite
    return NO;
}

- (void) startInvitedGame{
    
}

- (void) selectGame{
    // TODO: Choose what type of game to play - UI Interface options
}



- (void) startGame{
    
}

- (void) joinGame{
    
}

#pragma mark - GAME



- (void) gameCycle{
    
    
}

- (void) setupMap{
    
}

/*
 *  Game will be peer-to-peer.  Each game instance will keep track of what tiles have been played, what tiles are in hands of all players and the max allowed tiles.  Each instance will randomly replenish player hands, checking first against what is in play, and then notify all GM instances of what new tiles were added to the pool.  Once the pool is reached it's maximum number of a given tile type, then that tile can not be added to any players hands.  Once the maximum number of tiles have been reached, then no new tiles will be made available.
 */



#pragma mark - POST GAME

- (void) calculatePoints{
    
}

- (void) determinPlayersRankings{
    
}

- (void) replayVote{
    
}

@end
