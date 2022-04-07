#include <kipr/wombat.h>
int forwardSpeed=100;		// speed moving forwards (mm/s)
int backSpeed=-100;				// speed moving backwards (mm/s)
int interval=10;					// msleep interval in while loop
int cm = 10;						// mm -> cm
int lightPort = 4;				// light port
int clawPort = 3;			 //claw port
int armPort = 0;             //arm port
int up;
int down;
int storage;
int open = 630;				// claw open position
int closed = 1750;			//claw closed position
int clawWait = 1000; 	//wait 1 second for claw to change position

void Forward(float distance);								//move forward for certain distance (cm)
void Backwards(float distance);							//move backwards for certain distance (cm)
void Left(float angle);											//turn left at certain angle (degrees)
void Right(float angle);										//turn right at certain angle (degrees)
void Claw(int position);										//set claw position 
void Arm(int position);											//set arm position

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
    wait_for_light(lightPort);													//wait for light before starting
    
    shut_down_in(115);																//shut down robot 5 secs before game ends
   
    create_connect();																//connect create
    
	Claw(open);																			//open claw
    
	Forward(20);																		// move forwards 10 cm
	
	Right(90);																				//turn right 90 degrees
    
    Forward(150);																		// move forwards 150 cm
    
   	Claw(closed);																		//close claw
    
    Arm(up);																			//lift arm
    
    Forward(5);																			//move forward so arm is above transporter
    
    Arm(down);																		//lower arm
    
    Claw(open);																			//open claw to drop poms in transporter
    
    //--------------------------------------------------------------------------------------------------------------------------
    
    Backwards(30);																	//drag transporter back 30cm
    
    Right(10);																			//turn right 10 degrees
    
    Backwards(150);																	//move back into starting box
    
    Right(35);																			//turn right 35 degrees
    
    Backwards(10);																	//move backwards 10cm
    
    Right(35);																			//turn right 35 degrees
    
    Backwards(10);																	//move backwards 10cm
    
    Right(35);																			//turn right 35 degrees
    
    Arm(up);																	//lift arm up
    
    Backwards(70);																	//move backwards 70cm to storage rack
    
    Left(90);																			//turn 90 degrees left
    
    //--------------------------------------------------------------------------------------------------------------------------
    
    Forward(80);																			//push all cubes to side
    
    Backwards(10);																		//move backwards 10cm
    
    Right(80);																					//turn right 80 degrees
    
    Forward(30);																			//move forward 30cm
    
    Left(160);																					//turn around to face track
    
    Arm(storage);																			//move arm to storage rack level
    
    Forward(30);																			//move forward 30cm to storage rack
    
    Claw(closed);																			//close arm to pick up cubes
    
    Backwards(50);																		//move cubes back to black line
    
    Claw(open);																				//drop cubes on line
    
    Backwards(30);																		//move back 30cm
    
    Right(80);																				//turn right to be 90 degrees along rack
    
    Forward(50);																		//move forward 50 degrees
    
    Right(90);																				//turn right 90 degrees
    
    Backwards(75);																		//move 75cm back to rack
    
    Left(90);																				//turn left 90 degrees
    
//				2nd cube collection
    
    Forward(80);																		//push all cubes to side
    
    Backwards(10);																		//move backwards 10cm
    
    Right(80);																					//turn right 80 degrees
    
    Forward(30);																			//move forward 30cm
    
    Left(160);																					//turn around to face track
    
    Arm(storage);																			//move arm to storage rack level
    
    Forward(30);																			//move forward 30cm to storage rack
    
    Claw(closed);																			//close arm to pick up cubes
    
    Backwards(50);																		//move cubes back to black line
    
    Claw(open);																				//drop cubes on line
    
    
    
    create_disconnect();														//disconnect create
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Forward(float distance) {																			//move forward x cm
    set_create_distance(0);																			
    while ((get_create_distance())<(distance*cm)) {
        create_drive_direct(forwardSpeed,forwardSpeed);
        msleep(interval);
    }}

void Backwards(float distance) {																			//move backwards x cm
	set_create_distance(0);
    while ((abs((get_create_total_angle())))<(distance*cm)) {
        create_drive_direct(backSpeed,backSpeed);
        msleep(interval);
    }}

void Left(float angle) {																			//turn left x degrees
    set_create_total_angle(0);
    while ((get_create_total_angle())<angle) {
        create_drive_direct(backSpeed,forwardSpeed);
        msleep(interval);
    }}

void Right(float angle) {																			//turn right x degrees
    set_create_total_angle(0);
    while ((abs((get_create_total_angle())))<angle) {
        create_drive_direct(forwardSpeed,backSpeed);
        msleep(interval);
    }}

void Claw(int position) {																			//change claw's position (open/closed)
    set_servo_position(clawPort,position);
    enable_servos();
    msleep(clawWait);
    disable_servos();
   
}

void Arm(int position) {																			//change claw's position (open/closed)
    set_servo_position(armPort,position);
    enable_servos();
    msleep(clawWait);
    disable_servos();
}
