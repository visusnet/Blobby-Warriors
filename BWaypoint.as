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
	
	public class BWaypoint
	{
		// etc
		public var posx:int;
		public var posy:int;
		
		public var id:int;
		
		public var connection:Array;
		
		
		
		public function toXML():String
		{
			var xml_string:String;
			
			xml_string = "<waypoint id='" + id + "' posx='" + posx + "' posy='" + posy + "'>";
			
			for each(var i:Array in connection)
				xml_string += "\n\t<waypoint_con_id id='" + i[0] + "' length='" + i[1] + "'></waypoint_con_id>";
			
			xml_string += "\n</waypoint>";
			
			return xml_string;
		}
		
		
		public function BWaypoint(id:int, posx:int, posy:int, connection:Array)
		{
			this.id = id;
			this.posx = posx;
			this.posy = posy;
			this.connection = connection;
		}
	}
}













