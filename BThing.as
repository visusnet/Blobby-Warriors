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
	
	// Triangulation
	import com.indiemaps.delaunay.*;
	
	
	public class BThing
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var health:Number;
		public var health_full:Number
		
		public var userData:BitmapData;
		public var bodyDef:b2BodyDef;
		public var polyDef:b2PolygonDef;
		public var body:b2Body;
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BThing";
		public var ki:BKI;
		public var content:String = "";
		public var mass:Number;
		
		private var velocity:b2Vec2;
		
		
		
		public function destroy()
		{
			return;
			
			var phy_scale:Number = parent.config.phy_scaling;
			
			
			// alle Shapes des concave Polygons durchgehen und jedes
			// convex polygon triangulieren
			var shape_points:Array;
			var s:b2Shape;
			
			// alle Shapes durchgehen
			for(s = body.GetShapeList(); s; s = s.GetNext())
			{
				// shape_points Array cleanen
				shape_points = new Array();
				
				// Shape in b2PolygonShape konvertieren
				var s_poly:b2PolygonShape = s as b2PolygonShape;
				
				// alle Seitenpunkte durchgehen
				var tmp_m_vertices:Array = s_poly.GetVertices();
				for (var j:int = 0; j < s_poly.GetVertexCount(); j++)
				{
					var tmp_point:b2Vec2 = tmp_m_vertices[j] as b2Vec2;
					shape_points.push(new Point(tmp_point.x, tmp_point.y));
					
					trace(getTimer() + " verticle: " + (tmp_point.x * phy_scale) + " " + (tmp_point.y * phy_scale));
				}
				
				shape_points.push(new Point(0, 0));
				
				
				//trace(getTimer() + " normal: " + body.GetPosition().x + " " + body.GetPosition().y);
				
				
				// weiterenTreffpunkt einfügen
				//var tmp_point:b2Vec2 = tmp_m_vertices[0] as b2Vec2;
				
				/*var test_vec:b2Vec2 = new b2Vec2(-1 / phy_scale, 1 / phy_scale);
				
				var test_vec_world:b2Vec2 = new b2Vec2(test_vec.x + body.GetPosition().x, test_vec.y + body.GetPosition().y);
				
				if(s.TestPoint(body.GetXForm(), test_vec_world) == true)
				{
					//shape_points.push();
					trace(getTimer() + " yo.");
				}
				else
					trace(getTimer() + " no.");*/
				
				
				
				
				// anhand der ermittelten Punkte des convec-shapes triangulieren
				var triangles = Delaunay.triangulate(shape_points);
		
				trace(getTimer() + " triangles_count: " + triangles.length);
		
				for each(var tri:ITriangle in triangles)
				{
					// BodyDef
					var bodyDef = new b2BodyDef();
					bodyDef.position.x = body.GetPosition().x;
					bodyDef.position.y = body.GetPosition().y;
					bodyDef.isBullet = true;
					bodyDef.angle = body.GetAngle();
					
					// PolyDef
					var polyDef = new b2PolygonDef();
					polyDef.vertexCount = 3;
					polyDef.vertices[0].Set(shape_points[tri.p3].x, shape_points[tri.p3].y);
					polyDef.vertices[1].Set(shape_points[tri.p2].x, shape_points[tri.p2].y);
					polyDef.vertices[2].Set(shape_points[tri.p1].x , shape_points[tri.p1].y);
					polyDef.density = 0.3;
					polyDef.friction = 0.3;
					polyDef.restitution = 0.1;

					// Bitmap für Piece erstellen
					//var bmp_ori:BitmapData = new BitmapData(26,26, true, 0x00ffffff);
					//bmp_ori.draw(userData);
					var tmp_sprite:Sprite = new Sprite();
					tmp_sprite.addChild(new Bitmap(userData));
					
					// Polygon-Maske erstellen
					var polyMask:Sprite = new Sprite();
					polyMask.graphics.lineStyle(1, 0x000000);
					polyMask.graphics.beginFill(0x0000ff);

						polyMask.graphics.moveTo(shape_points[tri.p3].x * phy_scale + 13, shape_points[tri.p3].y * phy_scale + 13);
						polyMask.graphics.lineTo(shape_points[tri.p2].x * phy_scale + 13, shape_points[tri.p2].y * phy_scale + 13);
						polyMask.graphics.lineTo(shape_points[tri.p1].x * phy_scale + 13, shape_points[tri.p1].y * phy_scale + 13);
						
					polyMask.graphics.endFill();
			
			
					tmp_sprite.mask = polyMask;
			
					// Maskierte Sprite a
					var new_bmp:BitmapData = new BitmapData(100,100, true, 0x00ffffff);
					new_bmp.draw(tmp_sprite);
					
					// Piece erstellen
					var tmp_thing:BThing = new BThing(parent, 0, new_bmp, 50, bodyDef, polyDef, body.GetLinearVelocity());
					tmp_thing.add();
					
					trace(getTimer() + " main thing: " + body.GetPosition().x + " " + body.GetPosition().y);
					trace(getTimer() + " new thing: " + tmp_thing.body.GetPosition().x + " " + tmp_thing.body.GetPosition().y);
				}
			}
		}
		
		
		public function add()
		{
			body=parent.level.m_world.CreateBody(bodyDef);
			
			body.CreateShape(polyDef);
			
			if(mass!=0)
			{
				var tmp_mass:b2MassData = new b2MassData();
				tmp_mass.mass = mass;
				tmp_mass.I = 3;
				
				tmp_mass.center.SetZero();
				//tmp_mass.center.x -= 13 / parent.config.phy_scaling;
				//tmp_mass.center.y -= 13 / parent.config.phy_scaling;
				
				body.SetMass(tmp_mass);
			}
			else
			{
				body.SetMassFromShapes();
			}
			
			//body.SetLinearVelocity(velocity);
		}
		
		public function bdraw()
		{
			var trans_x:Number = 13;
			var trans_y:Number = 13;
			var trans_x2:Number = 4;
			var trans_y2:Number = 4;
			
			var angle_in_radians = body.GetAngle();
			
			var rotationMatrix:Matrix = new Matrix();
			rotationMatrix.translate(-trans_x,-trans_y);
			rotationMatrix.rotate(angle_in_radians);
			rotationMatrix.translate(trans_x,trans_y);
			
			rotationMatrix.tx += trans_x2;
			rotationMatrix.ty += trans_y2;
			
			var matrixImage:BitmapData = new BitmapData(34, 34, true, 0x00000000);
			matrixImage.draw(userData, rotationMatrix);

			var playerRect:Rectangle = new Rectangle(0,0,34,34);
			var playerPoint:Point=new Point(((body.GetPosition().x-(trans_x+trans_x2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollX,((body.GetPosition().y-(trans_y+trans_y2)/parent.config.phy_scaling) * parent.config.phy_scaling) - parent.scrollY);
			parent.canvasBD.copyPixels(matrixImage, playerRect, playerPoint);
		}
		
		public function BThing(p:BGame, mass:Number, image:BitmapData, health_full:int, bodyDef:b2BodyDef, polyDef:b2PolygonDef, velocity:b2Vec2)
		{
			parent = p;
			var phy_scale:Number = parent.config.phy_scaling;
			
			// BodyDef
			this.bodyDef = bodyDef;
			bodyDef.userData = this;
			
			// PolyDef
			this.polyDef = polyDef;
				
			// health
			this.health_full = health_full;
			health = health_full;
			
			// image
			this.userData = image;
			
			// mass
			this.mass = mass;
			
			// Speed
			this.velocity = velocity;
		}
		
	}
}













