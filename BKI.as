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
	
	public class BKI
	{
		// ### Atributes ###
		public var parent:BGame;
		public var bobject:*;
		public var id:int=666;
	
		// Keyboard
		var Key_Array:Array = new Array();
		
		// Waypoints
		public var waypoints:Array;
		public var waypoints_last:Array;
		private var waypoint_jump_start=0;
		private var waypoint_jump1_time=0;
		private var waypoint_jump2_time=0;
		
		// Timer
		private var timer_calc_way_last = getTimer();
		private var timer_calc_way_time = 5000;
		
		// Wegberechnung
		var bway:BDijkstra;
		

		public function BKI(p:BGame, body:b2Body)
		{
			parent = p;
			
			bobject = body.GetUserData();
			bobject.ki = this;
			
			
			// test Waypoints
			waypoints = new Array();
			waypoints_last = new Array();
			
			// Keyboard
			for (var i:Number = 0; i < 255; i++)
			{
				Key_Array[i] = new BKey();
			}
			
			// Wegberechnung
			bway = new BDijkstra(parent.level.waypoint_array);
		}
		
		public function move_to(ziel:b2Vec2)
		{
			var start:b2Vec2 = new b2Vec2(bobject.body.GetPosition().x * parent.config.phy_scaling, bobject.body.GetPosition().y * parent.config.phy_scaling);
			
			ziel.x *= parent.config.phy_scaling;
			ziel.y *= parent.config.phy_scaling;
			
			var tmp_array:Array = new Array();
			tmp_array = bway.calc(parent.level.get_newest_waypoint(start), parent.level.get_newest_waypoint(ziel));
		
			for each(var str:String in tmp_array)
				trace(str + " -> ");		
		
			// nur wenn sich der Weg geändert hat
			if(tmp_array.length == waypoints_last.length)
			{
				var error:Boolean = false;
				for(var i:int=0; i<tmp_array.length; i++)
				{
					if(tmp_array[i]!=waypoints_last[i])
					{
						error = true;
						break;
					}
				}
				
				if(error == true)
				{
					waypoints = new Array();
					for each(var tmp_wp:BWaypoint in tmp_array)
						waypoints.push(tmp_wp);
					
					waypoints_last = new Array();
					for each(tmp_wp in waypoints)
						waypoints_last.push(tmp_wp);
				}
			}
			else
			{
				waypoints = new Array();
				for each(var tmp_wp2:BWaypoint in tmp_array)
					waypoints.push(tmp_wp2);
				
				waypoints_last = new Array();
				for each(tmp_wp2 in waypoints)
					waypoints_last.push(tmp_wp2);
			}
		}
		
		private function calc_way()
		{
			if(getTimer() - timer_calc_way_last > timer_calc_way_time)
			{
				move_to(new b2Vec2(parent.level.player.body.GetPosition().x, parent.level.player.body.GetPosition().y));
				timer_calc_way_last = getTimer();
			}
		}
		
		public function step()
		{
			if(parent.level.player.health<=0)
			{
				bobject.keyboard_control("up", true, 301);
				bobject.mouse_control("mouse_up", true, 0, 0);
				return;
			}
				
			// defs
			var abstand:Number = Math.abs(parent.level.player.body.GetPosition().x - bobject.body.GetPosition().x) * parent.config.phy_scaling;
			
			
			// Zielroute überprüfen
			calc_way();
			
			
			// Movement / Waypoints
			var my_wpoint:BWaypoint = waypoints.pop();
			if(my_wpoint!=null)
			{
				waypoints.push(my_wpoint);
	
				var tmp_abstand_verti:int = (bobject.body.GetPosition().y * parent.config.phy_scaling) - my_wpoint.posy;
				var tmp_abstand_hori:int = (bobject.body.GetPosition().x * parent.config.phy_scaling) - my_wpoint.posx;
				
				if(tmp_abstand_verti > 30)
				{
					if(waypoint_jump_start==0)
					{
						waypoint_jump_start=getTimer();
						
						var tmp_time:int = tmp_abstand_verti * 3.1;
						
						if(tmp_abstand_verti > 130)
						{
							waypoint_jump1_time=tmp_time/2;
							waypoint_jump2_time=tmp_time/2;
						}
						else
						{
							waypoint_jump1_time=tmp_time;
							waypoint_jump2_time=0;
						}
					}
				}
				else
					Key_Array[87].up();
				
				
				/*if(waypoint_jump_start == 0)
				{*/
					if(bobject.body.GetPosition().x < (my_wpoint.posx / parent.config.phy_scaling))
						Key_Array[68].down();
					else
						Key_Array[68].up();
						
					
						
					if(bobject.body.GetPosition().x > (my_wpoint.posx / parent.config.phy_scaling))
						Key_Array[65].down();
					else
						Key_Array[65].up();
				/*}
				else
				{
					Key_Array[68].up();
					Key_Array[65].up();
					
					trace(getTimer() + " hier");
				}*/
				
				
				
				var tol_x:int = 10;
				var tol_y:int = 20;
				if(bobject.body.GetWorldCenter().x > ((my_wpoint.posx-tol_x) / parent.config.phy_scaling) &&
						bobject.body.GetWorldCenter().x < ((my_wpoint.posx+tol_x) / parent.config.phy_scaling) &&
							bobject.body.GetWorldCenter().y < ((my_wpoint.posy+tol_y) / parent.config.phy_scaling) &&
								bobject.body.GetWorldCenter().y > ((my_wpoint.posy-tol_y) / parent.config.phy_scaling))
						//trace(waypoints.pop().id);
						waypoints.pop();
				
			}
			else
			{
				Key_Array[68].up();
				Key_Array[65].up();
			}
			
			
			// Jump Handling
			if(waypoint_jump_start!=0)
			{
				if(waypoint_jump1_time!=0)
				{
					if(getTimer() - waypoint_jump_start < waypoint_jump1_time)
					{
						Key_Array[87].down();
					}
					else
					{
						waypoint_jump1_time = 0;
						
						if(waypoint_jump2_time == 0)
							waypoint_jump_start = 0;
						else
							waypoint_jump_start = getTimer();
						
						Key_Array[87].up();
					}
				}
				else if(waypoint_jump2_time!=0)
				{
					if(getTimer() - waypoint_jump_start < waypoint_jump2_time)
					{
						Key_Array[87].down();
					}
					else
					{
						waypoint_jump2_time = 0;
						waypoint_jump_start = 0;
					}
				}
			}
			
			// Handle Input
			if (Key_Array[68].isPressed() == true || Key_Array[68].hasChanged() == true)
			{
				bobject.keyboard_control("right", Key_Array[68].pressed, Key_Array[68].time_pressedTotal);
			}
			if (Key_Array[65].isPressed() == true || Key_Array[65].hasChanged() == true)
			{
				bobject.keyboard_control("left", Key_Array[65].pressed, Key_Array[65].time_pressedTotal);
			}
			if (Key_Array[87].isPressed() == true || Key_Array[87].hasChanged() == true)
			{
				bobject.keyboard_control("up", Key_Array[87].pressed, Key_Array[87].time_pressedTotal);
			}
			
			



			// weapon angle
			if(bobject.weapon!=null)
			{
				if(abstand < 300)
				{
					var tmp_x:Number = (bobject.body.GetWorldCenter().x * parent.config.phy_scaling);
					var tmp_y:Number = (bobject.body.GetWorldCenter().y * parent.config.phy_scaling);
					
					var a:int = ((parent.level.player.body.GetWorldCenter().y * parent.config.phy_scaling) - parent.scrollY ) - (tmp_y) + parent.scrollY;
					var b:int = ((parent.level.player.body.GetWorldCenter().x * parent.config.phy_scaling) - parent.scrollX ) - (tmp_x) + parent.scrollX;
	
					bobject.weapon.angle = Math.atan2(a / parent.config.phy_scaling, b / parent.config.phy_scaling);
					bobject.weapon.angle_middle = bobject.weapon.angle;
				}
			}
			
			// shoot
			if(abstand < 300 && Math.random()<0.3)
				bobject.mouse_control("mouse_down", true, 0, 0);
			else
				bobject.mouse_control("mouse_up", true, 0, 0);
		}		
	}
}













