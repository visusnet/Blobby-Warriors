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
	import flash.geom.*;
	

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
	
	public class BPlayerLeiste
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var userData:playerleiste_1;
		
		public var display:playerleiste_display;

		
		public function show()
		{
			parent.addChild(userData);
			userData.addChild(display);
			display.x = 17;
			display.y = 7;
		}
		
		public function hide()
		{
			parent.removeChild(userData);
		}
		
		public function refresh()
		{
			
		}

		public function BPlayerLeiste(p:BGame)
		{
			parent = p;
			
			userData = new playerleiste_1();
			userData.x = 0;
			userData.y = 500;
			/*userData.width = (circleDef.radius * 2) * phy_scale; 
			userData.height = (circleDef.radius * 2) * phy_scale;*/
			
			display = new playerleiste_display();
		}
	}
}













