//
//  SRMapVC.h
//  Silkroad
//
//  Created by Jason Koo on 9/10/13.
//  Copyright (c) 2013 SilkRoad. All rights reserved.
//
//  BRIEF: This class handles the actual display and animation effects during the game
//  MENU & Gameplay interfaces will have their own ViewControllers but will be instantiated and coordinated here

#import <UIKit/UIKit.h>
#import "SRMap.h"

@class SRMap;

@interface SRMapVC : UIViewController

@property (nonatomic, strong)   SRMap           *map;
@property (nonatomic, weak)     UIScrollView    *canvas; // To allow players to zoom in and out of map




@end
