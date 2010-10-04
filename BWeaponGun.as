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
	
	public class BWeaponGun extends BWeapon
	{
		public function bdraw()
		{
			var trans_x:Number = 40/2;
			var trans_y:Number = 19/2;
			var trans_x2:Number = 20;
			var trans_y2:Number = 30;
			
			var angle_in_radians = body.GetAngle();
			
			var rotationMatrix:Matrix = new Matrix();
			rotationMatrix.translate(-trans_x,-trans_y);
			rotationMatrix.rotate(angle_in_radians);
			rotationMatrix.translate(trans_x,trans_y);
			
			rotationMatrix.tx += trans_x2;
			rotationMatrix.ty += trans_y2;
			
			var matrixImage:BitmapData = new BitmapData(80, 80, true, 0x00000000);
			matrixImage.draw(userData, rotationMatrix);
		
			var playerRect:Rectangle = new Rectangle(0,0,80,80);
			var playerPoint:Point=new Point(((body.GetPosition().x-(trans_x+trans_x2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollX,((body.GetPosition().y-(trans_y+trans_y2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollY);
			parent.canvasBD.copyPixels(matrixImage, playerRect, new Point(playerPoint.x, playerPoint.y));
		}
		
		public function create(x:int, y:int, scale:Boolean)
		{
			var phy_scale:Number = parent.config.phy_scaling;
			
			
			bodyDef = new b2BodyDef();
			polyDef = new b2PolygonDef();
			
			polyDef.vertexCount = 6;
			polyDef.vertices[0].Set(0 / phy_scale,3 / phy_scale);
			polyDef.vertices[1].Set(13 / phy_scale,1 / phy_scale);
			polyDef.vertices[2].Set(39 / phy_scale,3 / phy_scale);
			polyDef.vertices[3].Set(40 / phy_scale,13 / phy_scale);
			polyDef.vertices[4].Set(22 / phy_scale,18 / phy_scale);
			polyDef.vertices[5].Set(0 / phy_scale,12 / phy_scale);
			polyDef.density = 0.3;
			polyDef.friction = 0.3;
			polyDef.restitution = 0.1;
			polyDef.categoryBits = 0x0004;
			
			bodyDef.position.x = x / phy_scale;
			bodyDef.position.y = y / phy_scale;
			bodyDef.userData = this;
			bodyDef.allowSleep = true;
			
			if(direction==1)
			{
				change_carry_direction();
			}
		}
		
		public function BWeaponGun(p:BGame, x:int, y:int)
		{
			parent = p;
			
			
			create(x,y,false);
			
			userData = new object_weaponGun();
			//userData.x = 585;
			//userData.y = 40;s
			userData.width = 40;
			userData.height = 19;
			
			
			blobbyX_draw = 3;
			blobbyY_draw = 3;
			
			blobbyX_rotate = 3;
			blobbyY_rotate = 3;
			
			load_max_time = 200;
			power = 350;
			type = "BWeaponGun";
			
			direction = 0;
		}
		
		public function shoot(carry_rotation:Number)
		{
			var tmp_x:Number = parent.level.player.body.GetPosition().x + (20 - 3)/parent.config.phy_scaling;
			var tmp_y:Number = parent.level.player.body.GetPosition().y + (23.5 - 3)/parent.config.phy_scaling;
			
			var test_moniGun:BMonitionGun = new BMonitionGun(parent, tmp_x, tmp_y);
			
			test_moniGun.add();
			
			test_moniGun.body.m_linearVelocity = parent.mouse_angle_vec;
			test_moniGun.body.m_linearVelocity.x *= (power/parent.config.phy_scaling) * test_moniGun.body.GetMass();
			test_moniGun.body.m_linearVelocity.y *= (power/parent.config.phy_scaling) * test_moniGun.body.GetMass();
			
			//test_moniGun.body.m_sweep.a = rotation + carry_rotation;
		}		
	}
}













