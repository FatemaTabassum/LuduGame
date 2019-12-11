//
//  Backend.hpp
//  DiceLuduGame
//
//  Created by Sajib on 5/12/19.
//  Copyright © 2019 Liza. All rights reserved.
//

#ifndef Backend_hpp
#define Backend_hpp

#include <stdio.h>
#include "Friend.hpp"
#include <pthread.h>
#include <unistd.h>

// Declaration of thread condition variable
extern pthread_cond_t cond1;

// declaring mutex
extern pthread_mutex_t lock;

void takeInput();

#endif /* Backend_hpp */

