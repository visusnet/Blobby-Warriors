package
{
	// Flash
	import flash.events.Event;
	import flash.display.*;
	import flash.text.*;
	import flash.events.*;
	import flash.system.*;
	import flash.ui.*;
	import flash.utils.getTimer;
	import flash.display.MovieClip;
	import flash.net.URLRequest;

	// Physic
	import Box2D.Dynamics.*;
	import Box2D.Collision.*;
	import Box2D.Collision.Shapes.*;
	import Box2D.Common.Math.*;
	import Box2D.Dynamics.Joints.*;
	import Box2D.Dynamics.Contacts.*;
	import Box2D.Dynamics.*;
	import Box2D.Common.*;
	import General.*;
	
	public class BWeapon
	{
		// ### Atributes ###
		public var userData:*;
		public var bodyDef:b2BodyDef;
		public var body:b2Body;
		
		public var blobbyX_draw:int;
		public var blobbyY_draw:int;
		
		public var blobbyX_rotate:int;
		public var blobbyY_rotate:int;
		
		public var gravity_master:Boolean = false;
		
		public var type:String;
		
		public var direction:int;
		
		public var power;
		
		
		// ladezeit
		public var load_time_start:int;
		public var load_max_time:int;
		
		public function check_for_shoot():Boolean
		{
			if(getTimer() - load_time_start > load_max_time)
			{
				load_time_start = getTimer();
				
				return true;
			}
			
			return false;
		}
					
		
		
		public function change_carry_direction()
		{
			blobbyX_draw *= -1;
			blobbyX_rotate *= -1;
			
			//userData.scaleX *= -1;
			userData.scaleY *= -1;
			
			if(direction == 0)
				direction = 1;
			else
				direction = 0;
		}
		
	}
}













