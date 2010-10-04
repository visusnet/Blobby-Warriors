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
	import flash.geom.*;
	
	public class BWeaponLaserGreen extends BWeapon
	{
		public function bdraw()
		{
			var trans_x:Number = 50/2;
			var trans_y:Number = 20/2;
			var trans_x2:Number = 15;
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
		
		public function create(x:int, y:int,scale:Boolean)
		{
			var phy_scale:Number = parent.config.phy_scaling;
			
			
			bodyDef = new b2BodyDef();
			polyDef = new b2PolygonDef();
			
			/*polyDef.vertexCount = 4;
			polyDef.vertices[0].Set(1 / phy_scale,0 / phy_scale);
			polyDef.vertices[1].Set(35 / phy_scale,0 / phy_scale);
			polyDef.vertices[2].Set(48 / phy_scale,6 / phy_scale);
			polyDef.vertices[3].Set(8 / phy_scale,18 / phy_scale);*/
			
			polyDef.vertexCount = 4;
			polyDef.vertices[0].Set(1 / phy_scale,0 / phy_scale);
			polyDef.vertices[1].Set(35 / phy_scale,0 / phy_scale);
			polyDef.vertices[2].Set(48 / phy_scale,6 / phy_scale);
			polyDef.vertices[3].Set(8 / phy_scale,18 / phy_scale);
				
			if(direction==1)
			{
				change_carry_direction();
			}

			polyDef.density = 0.3;
			polyDef.friction = 0.3;
			polyDef.restitution = 0.1;
			polyDef.categoryBits = 0x0004;
			
			bodyDef.position.x = x / phy_scale;
			bodyDef.position.y = y / phy_scale;
			bodyDef.userData = this;
			bodyDef.allowSleep = true;
		}
		
		public function BWeaponLaserGreen(p:BGame, x:int, y:int)
		{
			parent = p;
			
			
			create(x,y,false);
			
			userData = new object_weaponLaserGreen();
			//userData.x = 585;
			//userData.y = 40;
			userData.width = 40;
			userData.height = 19;
			
			
			blobbyX_draw = 7;
			blobbyY_draw = 3;
			
			blobbyX_rotate = 120;
			blobbyY_rotate = 0;
			
			
			load_max_time = 400;
			type = "BWeaponLaserGreen";
			power = 300;
			
			direction = 0;
		}
		
		public function shoot(carry_rotation:Number)
		{
			var tmp_x:Number = parent.level.player.body.GetPosition().x + (20 - 3)/parent.config.phy_scaling;
			var tmp_y:Number = parent.level.player.body.GetPosition().y + (23.5 - 3)/parent.config.phy_scaling;
			
			var test_moniLaserGreen:BMonitionLaserGreen = new BMonitionLaserGreen(parent, tmp_x, tmp_y);
			
			test_moniLaserGreen.add();
			
			test_moniLaserGreen.body.m_linearVelocity = parent.mouse_angle_vec;
			test_moniLaserGreen.body.m_linearVelocity.x *= (power/parent.config.phy_scaling) * test_moniLaserGreen.body.GetMass();
			test_moniLaserGreen.body.m_linearVelocity.y *= (power/parent.config.phy_scaling) * test_moniLaserGreen.body.GetMass();
			
			test_moniLaserGreen.body.m_sweep.a = parent.mouse_angle + carry_rotation;
		}		
	}
}













