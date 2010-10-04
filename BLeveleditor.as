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
	import flash.xml.*;
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
	
	public class BLeveleditor
	{
		// ### Atributes ###
		public var parent:BGame;
		public var status=false;
		public var action:int = 0;		// edit GroundLine... edit Waypoint
		
		public var p1:Point;
		public var p2:Point;
		
		public var m_sprite:Sprite;
		public var m_menu:BLeveleditor_menu;
		
		public var last_waypoint_id:int;
		
		private var tmp_groundline:BGroundLine;
		
		
		
		public function BLeveleditor(p:BGame)
		{
			parent = p;
			m_sprite = new Sprite();
			
			// Menu
			m_menu = new BLeveleditor_menu();
			
			// Waypoint
			last_waypoint_id = -1;
		}
		
		public function change_action(action:int)
		{
			this.action = action;
			p1 = null;
			p2 = null;
			
			// Waypoints
			last_waypoint_id = -1;
			
			trace(getTimer() + " set action to: " + action);
		}
		
		
		public function click_on_waypoint(pos:Point) : int
		{
			for each(var Bwp:BWaypoint in parent.level.waypoint_array)
			{
				var a:int = pos.x - Bwp.posx;
				var b:int = pos.y - Bwp.posy;
				var c:int = Math.sqrt((a*a) + (b*b));
				
				if(c<5)
					return Bwp.id;				
			}
			
			return -1;
		}
		
		
		public function keyboard_control(s_name:String)
		{
			// action
			if(s_name == "esc")
			{
				change_action(0);
			}
			
			else if(s_name == "down")
			{
				var tmp_vec:b2Vec2 = new b2Vec2(tmp_groundline.body.GetPosition().x, tmp_groundline.body.GetPosition().y + (1/parent.config.phy_scaling));
				tmp_groundline.body.SetXForm(tmp_vec, tmp_groundline.body.GetAngle());
			}
			
			else if(s_name == "up")
			{
				var tmp_vec:b2Vec2 = new b2Vec2(tmp_groundline.body.GetPosition().x, tmp_groundline.body.GetPosition().y - (1/parent.config.phy_scaling));
				tmp_groundline.body.SetXForm(tmp_vec, tmp_groundline.body.GetAngle());
			}
			
			else if(s_name == "left")
			{
				var tmp_vec:b2Vec2 = new b2Vec2(tmp_groundline.body.GetPosition().x - (1/parent.config.phy_scaling), tmp_groundline.body.GetPosition().y);
				tmp_groundline.body.SetXForm(tmp_vec, tmp_groundline.body.GetAngle());
			}
			
			else if(s_name == "right")
			{
				var tmp_vec:b2Vec2 = new b2Vec2(tmp_groundline.body.GetPosition().x + (1/parent.config.phy_scaling), tmp_groundline.body.GetPosition().y);
				tmp_groundline.body.SetXForm(tmp_vec, tmp_groundline.body.GetAngle());
			}
			
			else if(s_name == "del")
			{
				// letzte Groundline entfernen
				// items / waffen zeichnen
				for (var bb:b2Body = parent.level.m_world.m_bodyList; bb; bb = bb.m_next)
				{
					if (bb.m_userData != null)
					{
						// items / waffen zeichnen
						if(bb.m_userData.type == "BGroundLine")
						{
							if(bb.m_userData == tmp_groundline)
							{
								parent.level.destroy_body(false, bb);
							}
						}
					}
				}
			}
		}
		
		
		
		
		public function mouse_control(s_name:String, i_time:int, x:int, y:int)
		{
			// action
			if(s_name == "mouse_move")
			{
				m_sprite.graphics.clear();
				
				
				// BGroundline
				if(action == 1)
				{
					if(p1!=null)
					{
						m_sprite.graphics.lineStyle(3, new b2Color(0.5,0,0).color, 1);
						m_sprite.graphics.moveTo(p1.x-parent.scrollX, p1.y-parent.scrollY);
						m_sprite.graphics.lineTo(x, y);
					}
				}
				
				// BWaypoint
				else if(action == 2)
				{
					if(last_waypoint_id != -1)
					{
						var tmp_wp:BWaypoint = parent.level.get_waypoint(last_waypoint_id);
						
						m_sprite.graphics.lineStyle(1, new b2Color(0.5,0,0).color, 1);
						m_sprite.graphics.moveTo(tmp_wp.posx-parent.scrollX, tmp_wp.posy-parent.scrollY);
						m_sprite.graphics.lineTo(x, y);
						
					}
					
					m_sprite.graphics.lineStyle(5, new b2Color(0.5,0,0).color, 1);
					m_sprite.graphics.moveTo(x, y);
					m_sprite.graphics.lineTo(x+1, y+1);
				}
				
				// BGroundline Del
				else if(action == -1)
				{
				}
				
				// BWaypoint Del
				else if(action == -2)
				{
				}
			}
			
			else if(s_name == "mouse_down")
			{
				trace(getTimer() + " mouse_down, action: " + action);
				
				// BGroundline
				if(action == 1)
				{
					if(p1==null)
						p1=new Point(x+parent.scrollX,y+parent.scrollY);
					else
					{
						p2=new Point(x+parent.scrollX,y+parent.scrollY)
						
						if(p1.x<p2.x)
							tmp_groundline = new BGroundLine(parent, p1, p2, 1);
						else
							tmp_groundline = new BGroundLine(parent, p2, p1, 1);
							
						tmp_groundline.add();
						
						p1 = null;
						p2 = null;
					}					
				}
				
				// BWaypoint
				if(action == 2)
				{
					p1=new Point(x+parent.scrollX,y+parent.scrollY);
					
					var wp_id:int=-1;
					
					
					// wurde auf einen existierenden Waypoint geklickt?
					var clicked_waypoint:int = click_on_waypoint(p1);
					if(clicked_waypoint != -1)
					{
						if(last_waypoint_id!=-1)
						{
  							// connection bei dem letzen Waypoint erstellen
							var tmp_wp:BWaypoint = parent.level.get_waypoint(last_waypoint_id);
							tmp_wp.connection.push(new Array(clicked_waypoint, 10));
							
							// connection bei dem angeklickten bereits existierenden Waypoint erstellen
							var tmp_wp:BWaypoint = parent.level.get_waypoint(clicked_waypoint);
							tmp_wp.connection.push(new Array(last_waypoint_id, 10));
						}
						
						last_waypoint_id = clicked_waypoint;
					}
					else
					{					
						wp_id = parent.level.get_free_waypoint_id();
						
						// connection createn
						var con_array = new Array();
						
						if(last_waypoint_id!=-1)
						{
							con_array.push(new Array(last_waypoint_id, 10));
																		  
							var tmp_wp:BWaypoint = parent.level.get_waypoint(last_waypoint_id);
							tmp_wp.connection.push(new Array(wp_id, 10));
						}
							
						// neuen waypoints erstellen
						var tmp_waypoint:BWaypoint = new BWaypoint(wp_id, p1.x, p1.y, con_array);
						parent.level.waypoint_array.push(tmp_waypoint);
						
						last_waypoint_id = wp_id;
					}
				}
				
				
				// BGroundline Del
				else if(action == -1)
				{
					// wurde auf einen existierenden Waypoint geklickt?
					p1=new Point(x+parent.scrollX,y+parent.scrollY);
					/*p1.x-=2;
					p1.y-=2;*/
					
					var bb:b2Body;
						
					for (bb = parent.level.m_world.m_bodyList; bb; bb = bb.m_next)
					{
						if (bb.GetUserData() != null)
						{
							if(bb.GetUserData().type == "BGroundLine")
							{
								// Shape durchgehen
								var s:b2Shape;
								
								
								for (s = bb.GetShapeList(); s; s = s.GetNext())
								{
									for (var i:int = 0;i<1;i++)
									{
										if(s.TestPoint(bb.GetXForm(), new b2Vec2(p1.x/parent.config.phy_scaling, p1.y/parent.config.phy_scaling)))
										{
											parent.level.destroy_body(false, bb);
											parent.level.destroy_body(true, bb);
										}
										//p1.x++;
										//p1.y++;
									}
								}
									
									
							}
						}
					}
				}
				
				// BWaypoint Del
				else if(action == -2)
				{
					// wurde auf einen existierenden Waypoint geklickt?
					p1=new Point(x+parent.scrollX,y+parent.scrollY);
					
					var clicked_waypoint:int = click_on_waypoint(p1);
					if(clicked_waypoint != -1)
					{
						trace(getTimer() + " angeklickter waypoint: " + clicked_waypoint);
						
						
						// connection bei dem angeklickten bereits existierenden Waypoint durchgehen
						var tmp_wp:BWaypoint = parent.level.get_waypoint(clicked_waypoint);
						//tmp_wp.connection.push(new Array(last_waypoint_id, 10));
						
						for each(var tmp_array:Array in tmp_wp.connection)
						{
							// Den Waypoint der Connection ansprechen und bei ihm die Verbindung zum
							// angeklickten Waypoint löschen
							var tmp_con_wp:BWaypoint = parent.level.get_waypoint(tmp_array[0]);
							
							for each(var tmp_con_array:Array in tmp_con_wp.connection)
							{
								if(tmp_con_array[0] == clicked_waypoint)
								{
									trace(getTimer() + " delete connection to me from " + tmp_con_wp.id);
									
									var index:int = tmp_con_wp.connection.indexOf(tmp_con_array);
									tmp_con_wp.connection.splice(index, 1);
									
									break;
								}
							}
						}
						
						
						// angeklickten Waypoint entfernen
						for each(var tmp_wp_del:BWaypoint in parent.level.waypoint_array)
						{
							if(tmp_wp_del.id == clicked_waypoint)
							{
								var index:int = parent.level.waypoint_array.indexOf(tmp_wp_del);
								parent.level.waypoint_array.splice(index, 1);
								
								trace(getTimer() + " iam deletet know...");
							}
						}
					}
				}
				
				m_sprite.graphics.clear();
			}
			

			
			else if(s_name == "mouse_up")
			{
			}
			
			
		}
	}
}













