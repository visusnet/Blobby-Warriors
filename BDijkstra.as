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
	
	public class BDijkstra
	{
		public var ways:Array;
		public var waypoints:Array;
		public var start_id;
		public var stop_id;
		public var running:Boolean;
		public var way_result:Array;
		private var found_new_ways:Boolean;

		
		
		public function BDijkstra(waypoints:Array)
		{
			this.waypoints = waypoints;
			running = false;
		}
		
		public function get_waypoint(id:int) : BWaypoint
		{
			for each(var Bwp:BWaypoint in waypoints)
				if(Bwp.id == id)
					return Bwp;
			
			return null;			
		}
		
		public function check_way(BDWay:BDijkstraWay) : Boolean
		{
			var last_waypoint:BWaypoint = BDWay.waypoints[BDWay.waypoints.length-1];
			
			// Ende schon gefunden?
			if(last_waypoint.id == stop_id)
			{
				// Array speichern
				way_result = new Array();
				for (var i:int = BDWay.waypoints.length-1; i>=0; i--)
					way_result[i] = BDWay.waypoints[(BDWay.waypoints.length-1)-i];

				// Erfolg zurückgeben
				return true;
			}
			else
			{
				// alle connections des letzen Waypoints suchen
				// alle außer "zurück"
				var count:int = 0;
				for each(var Bwp_array:Array in last_waypoint.connection)
				{
					// nicht zurück gehen
					var back:Boolean = false;
					for each(var tmp_wp2:BWaypoint in BDWay.waypoints)
					{
						if(Bwp_array[0] == tmp_wp2.id)
						{
							back = true;
							continue;
						}
					}
					if(back==true)
						continue;
							
					// neuer weg wurde gefunden
					found_new_ways = true;
						
					var Bwp:BWaypoint = get_waypoint(Bwp_array[0]);
					
					// an aktuellen Way anhänhen
					if(count == 0)
					{
						BDWay.waypoints.push(Bwp);
					}
					
					// neuen Way erstellen
					else
					{
						var tmp_bway:BDijkstraWay = new BDijkstraWay();
						
						for(i=0;i<BDWay.waypoints.length;i++)
							tmp_bway.waypoints.push(BDWay.waypoints[i]);
						
						tmp_bway.waypoints.pop();
						tmp_bway.waypoints.push(Bwp);
						
						ways.push(tmp_bway);
					}
					
					count++;
				}
			}
			
			return false;
		}
		
		public function calc(start_id:int, stop_id:int) : Array
		{
			// init
			this.start_id = start_id;
			this.stop_id = stop_id;
			running= true;
			ways = new Array();
			
			// 1ten Way erstellen
			var tmp_first_bway:BDijkstraWay = new BDijkstraWay();
			tmp_first_bway.waypoints.push(get_waypoint(start_id));
			ways.push(tmp_first_bway);
			

			// Main Loop
			while(running == true)
			{
				found_new_ways = false;
				
				for each(var BDWay:BDijkstraWay in ways)
				{
					if(check_way(BDWay)==true)
					{
						return way_result;
					}
				}
				
				if(found_new_ways==false)
					running = false;
			}
			
			return new Array();
		}
	}
}













