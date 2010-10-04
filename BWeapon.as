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
	
	public class BWeapon
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var userData:*;
		public var bodyDef:b2BodyDef;
		public var polyDef:b2PolygonDef;
		public var body:b2Body;
		
		// Weapon bdraw
		var trans_x:Number;				// trans for draw
		var trans_y:Number;				// trans for draw
		var trans_x2:Number;			// trans2 for draw
		var trans_y2:Number;			// trans2 for draw
		var trans_BD_width:int;			// Bitmap Dimensions
		var trans_BD_height:int;		// Bitmap Dimensions
		var trans_x_carry:Number;		// trans for carry-draw
		var trans_y_carry:Number;		// trans for carry-draw
		var trans_x_move:int;			// move at the end of everting
		var trans_x_move_left:int;		// move at the end of everting left
		var trans_y_move:int;			// move at the end of everting
		var carry_middle_x:int;			// carry correction / rotation
		var carry_middle_x_left:int;	// carry correction / rotation left
		var carry_middle_y:int;			// carry correction / rotation
		
		
		// etc
		public var mass:Number;
		public var gravity_master:Boolean = false;
		public var direction:int;
		public var power;
		public var playerPointWeapon:Point;
		public var ttl:int=-1;
		public var carrier:b2Body;
		public var angle:Number=0;
		public var angle_middle:Number=0;
		
		public var type:String;
		public var pos:int;
		public var ki:BKI;
		public var content:String = "255,255,255";
		

		// ladezeit
		public var load_time_start:int;
		public var load_max_time:int;
		
		// sound
		public var sound:*;

		
		
		public function toXML():String
		{
			var xml_string:String;
			
			var tmp_position:Point = new Point(body.GetPosition().x * parent.config.phy_scaling, body.GetPosition().y * parent.config.phy_scaling);
			
			// ki id
			var ki_id:int = -1;
			if(ki != null)
				ki_id = ki.id;
				
			xml_string = "<object type='" + type + "' posx='" + tmp_position.x + "' posy='" + tmp_position.y + "' rotation='" + body.GetAngle() + "' ki='" + ki_id + "' content='" + content + "'></object>";
			
			return xml_string;
		}
		
		
		public function add()
		{
			body=parent.level.m_world.CreateBody(bodyDef);
			
			body.CreateShape(polyDef);
			
			body.SetMassFromShapes();
			/*var tmp_mass:b2MassData = new b2MassData();
			tmp_mass.mass = mass;
			tmp_mass.I = 3;
			tmp_mass.center.SetZero();
			body.SetMass(tmp_mass);*/
		}
		
		
		public function bdraw()
		{
			var angle_in_radians = body.GetAngle();
			
			var rotationMatrix:Matrix = new Matrix();
			rotationMatrix.translate(-trans_x,-trans_y);
			rotationMatrix.rotate(angle_in_radians);
			rotationMatrix.translate(trans_x,trans_y);
			
			rotationMatrix.tx += trans_x2;
			rotationMatrix.ty += trans_y2;
			
			var matrixImage:BitmapData = new BitmapData(trans_BD_width, trans_BD_height, true, 0x00000000);
			matrixImage.draw(userData, rotationMatrix);
		
			var playerRect:Rectangle = new Rectangle(0,0,trans_BD_width,trans_BD_height);
			var playerPoint:Point=new Point(((body.GetPosition().x-(trans_x+trans_x2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollX,((body.GetPosition().y-(trans_y+trans_y2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollY);
			
			parent.canvasBD.copyPixels(matrixImage, playerRect, new Point(playerPoint.x, playerPoint.y));
		}
		
		public function bdraw_carry(b:b2Body)
		{
			var angle_in_radians = angle + b.GetAngle();
			
			var rotationMatrix:Matrix = new Matrix();
				rotationMatrix.translate(-trans_x_carry,-trans_y_carry);
				
				// image flippen
				if(direction==1)
					rotationMatrix.scale(1,-1);
				
				rotationMatrix.rotate(angle_in_radians);
			rotationMatrix.translate(trans_x_carry,trans_y_carry);
			
			rotationMatrix.tx += trans_x2;
			rotationMatrix.ty += trans_y2;			
			
			
			var matrixImage:BitmapData = new BitmapData(trans_BD_width, trans_BD_height, true, 0x00000000);
			matrixImage.draw(userData, rotationMatrix);
		
		
		
			var playerRect:Rectangle = new Rectangle(0,0,trans_BD_width,trans_BD_height);
			
			var playerPoint:Point=new Point(((b.GetPosition().x-(trans_x_carry+trans_x2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollX,((b.GetPosition().y-(trans_y_carry+trans_y2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollY);
			
			playerPointWeapon = playerPoint;
			
			
			// waffenbewegung mit blobby
			if(carrier.GetUserData().GetDirection() == 1)
				playerPoint.x += trans_x_move_left;
			else
				playerPoint.x += trans_x_move;
				
			//playerPoint.x += trans_x_move;
				
			playerPoint.y += trans_y_move + getWeaponMovementFromCurFrame();
			
			
			parent.canvasBD.copyPixels(matrixImage, playerRect, new Point(playerPoint.x, playerPoint.y));
		}
		
		
				
		public function getWeaponMovementFromCurFrame() : int
		{
			if(carrier==null)
				return 0;

			var weapon_movement:int=0;
		
			if(carrier.GetUserData().frame_cur==1)
				weapon_movement = 1;
			else if(carrier.GetUserData().frame_cur==2)
				weapon_movement = 2;
			else if(carrier.GetUserData().frame_cur==3)
				weapon_movement = 3;
			else if(carrier.GetUserData().frame_cur==4)
				weapon_movement = 4;
			else if(carrier.GetUserData().frame_cur==5)
				weapon_movement = 5;
			else if(carrier.GetUserData().frame_cur==6)
				weapon_movement = 4;
			else if(carrier.GetUserData().frame_cur==7)
				weapon_movement = 3;
			else if(carrier.GetUserData().frame_cur==8)
				weapon_movement = 2;
				
				
			return weapon_movement;
		}
		
		
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
			userData.scaleY *= -1;
			
			if(direction == 0)
				direction = 1;
			else
				direction = 0;
		}
		
	}
}













