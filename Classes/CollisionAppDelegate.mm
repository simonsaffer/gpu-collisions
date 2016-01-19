//
//  CollisionAppDelegate.m
//  Collision
//
//  Created by Exjobb on 10/7/09.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import "CollisionAppDelegate.h"
#import "EAGLView.h"

@implementation CollisionAppDelegate

@synthesize window;
@synthesize glView;

- (void) applicationDidFinishLaunching:(UIApplication *)application
{
	[glView startAnimation];
}

- (void) applicationWillResignActive:(UIApplication *)application
{
	[glView stopAnimation];
}

- (void) applicationDidBecomeActive:(UIApplication *)application
{
	[glView startAnimation];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
	[glView stopAnimation];
}

- (void) dealloc
{
	[window release];
	[glView release];
	
	[super dealloc];
}

@end
