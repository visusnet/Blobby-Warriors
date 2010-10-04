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
	
	public class BConfig
	{
		// etc
		public var phy_scaling:Number;
		public var dimension_x:int;
		public var dimension_y:int;
		public var border_angle_jump:Number;
		public var sound:Boolean;
		
		// player scrolling
		public var border_x1:int;
		public var border_x2:int;
		public var border_y1:int;
		public var border_y2:int;
		
		// maximals
		public var max_waypoints:int;
		
		// collision
		public var categoryBits_bcrate:uint;
		public var categoryBits_bball:uint;
		public var categoryBits_bweaponlasergreen:uint;
		public var categoryBits_bweapongun:uint;
		public var categoryBits_bmonitionlasergreen:uint;
		public var categoryBits_bmonitiongun:uint;
		public var categoryBits_bgroundline:uint;
		public var categoryBits_bblobby:uint;
		
		public var maskBits_bcrate:uint;
		public var maskBits_bball:uint;
		public var maskBits_bweaponlasergreen:uint;
		public var maskBits_bweapongun:uint;
		public var maskBits_bmonitionlasergreen:uint;
		public var maskBits_bmonitiongun:uint;
		public var maskBits_bgroundline:uint;
		public var maskBits_bblobby:uint;
		public var maskBits_all:uint;
		
		public var groundline_height:uint;
		
		public function BConfig()
		{
			// collision
			categoryBits_bcrate = 0x0001;
			categoryBits_bball = 0x0001;
			categoryBits_bweaponlasergreen = 0x0001;
			categoryBits_bweapongun = 0x0001;
			categoryBits_bmonitionlasergreen = 0x0001;
			categoryBits_bmonitiongun = 0x0001;
			categoryBits_bgroundline = 0x0001;
			categoryBits_bblobby = 0x0001;
			
			maskBits_all = categoryBits_bcrate | categoryBits_bball | categoryBits_bweaponlasergreen | categoryBits_bweapongun | categoryBits_bmonitionlasergreen | categoryBits_bmonitiongun | categoryBits_bgroundline | categoryBits_bblobby;

			maskBits_bcrate = maskBits_all;
			maskBits_bball = maskBits_all;
			maskBits_bweaponlasergreen = maskBits_all;
			maskBits_bweapongun = maskBits_all;
			maskBits_bmonitionlasergreen = maskBits_all;
			maskBits_bmonitiongun = maskBits_all;
			maskBits_bgroundline = maskBits_all;
			maskBits_bblobby = maskBits_all;
			
			// etc
			phy_scaling = 10;
			dimension_x = 850;
			dimension_y = 550;
			border_angle_jump = 80;
			sound = true;
			
			// Calc Borders
			border_x1 = (dimension_x/100)*55;		// 55%
			border_x2 = (dimension_x/100)*45;		// 45%
			border_y1 = (dimension_y/100)*31.25;	// 31.25%
			border_y2 = (dimension_y/100)*43.75;	// 43.75%
			
			// maximals
			max_waypoints = 9999;
			
			// Groundline Height
			groundline_height = 1;
		}
	}
}













