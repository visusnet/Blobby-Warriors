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
		public var action:int = 1;		// edit GroundLine... edit Waypoint
		
		public var p1:Point;
		public var p2:Point;
		
		public var m_sprite:Sprite;
		
		
		
		public function BLeveleditor(p:BGame)
		{
			parent = p;
			m_sprite = new Sprite();
		}
		
		
		public function mouse_control(s_name:String, i_time:int, x:int, y:int)
		{
			// action
			if(s_name == "mouse_move")
			{
				m_sprite.graphics.clear();
				
				
				// BGroundline
				if(action == 0)
				{
					if(p1!=null)
					{
						
						m_sprite.graphics.lineStyle(3, new b2Color(0.5,0,0).color, 1);
						m_sprite.graphics.moveTo(p1.x-parent.scrollX, p1.y-parent.scrollY);
						m_sprite.graphics.lineTo(x, y);
					}
				}
				
				// BWaypoint
				else if(action == 1)
				{
					m_sprite.graphics.lineStyle(5, new b2Color(0.5,0,0).color, 1);
					m_sprite.graphics.moveTo(x, y);
					m_sprite.graphics.lineTo(x+1, y+1);
				}
			}
			
			else if(s_name == "mouse_down")
			{
				// BGroundline
				if(action == 0)
				{
					if(p1==null)
						p1=new Point(x+parent.scrollX,y+parent.scrollY);
					else
					{
						p2=new Point(x+parent.scrollX,y+parent.scrollY)
						
						var tmp_groundline:BGroundLine = new BGroundLine(parent, p1, p2, 1);
						tmp_groundline.add();
						
						p1 = null;
						p2 = null;
					}					
				}
				
				// BWaypoint
				if(action == 1)
				{
					p1=new Point(x+parent.scrollX,y+parent.scrollY);
					
					var tmp_waypoint:BWaypoint = new BWaypoint(23, p1.x, p1.y, new Array());
						
					parent.level.waypoint_array.push(tmp_waypoint);
				}
				
				m_sprite.graphics.clear();
			}
			
			else if(s_name == "mouse_up")
			{
			}
			
			
		}
	}
}













