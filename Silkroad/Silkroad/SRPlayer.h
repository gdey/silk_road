//
//  SRPlayer.h
//  Silkroad
//
//  Created by Jason Koo on 9/10/13.
//  Copyright (c) 2013 SilkRoad. All rights reserved.
//
//  BRIEF: This class will handle player creation, properties and image data
//  TYPES: Human, NPC

#import <Foundation/Foundation.h>

@interface SRPlayer : NSObject

@property (nonatomic, strong) struct    startingPosition;
@property (nonatomic, strong) NSString  *playerId;
@property (nonatomic, strong) NSString  *playerName;
@property (nonatomic, strong) NSNumber  *pointsEarned;
@property (nonatomic, strong) NSData    *imageData; // stub


@end
