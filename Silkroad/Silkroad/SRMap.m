//
//  SRMap.m
//  Silkroad
//
//  Created by Jason Koo on 9/10/13.
//  Copyright (c) 2013 SilkRoad. All rights reserved.
//

#import "SRMap.h"

@implementation SRMap

- (id) initForTilesWide:(int)numberWide long:(int)numberLong{
    self = [super init];
    if (!self) return nil;
    // TODO: generate graphics and set props
    
    _tilesWidth = numberWide;
    _tilesLength = numberLong;
    
    return self;
}

@end
