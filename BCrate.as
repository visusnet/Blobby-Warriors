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
	
	
	public class BCrate
	{
		// ### Atributes ###
		public var parent:BGame;
		
		public var health:Number;
		public var health_full:Number
		
		public var userData:object_crate;
		public var bodyDef:b2BodyDef;
		public var boxDef:b2PolygonDef;
		public var body:b2Body;
		
		public var gravity_master:Boolean = false;
		
		public var type:String = "BCrate";
		public var ki:BKI;
		public var content:String = "";
		
		
		public function destroy()
		{
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
				}
				
				// weiter strukturierter splitten
				shape_points.push(new Point(10/phy_scale, 0));
				
				// weiterenTreffpunkt einfügen
				//shape_points.push(new Point(50 / phy_scale, 220 / phy_scale));
				
				// anhand der ermittelten Punkte des convec-shapes triangulieren
				var triangles = Delaunay.triangulate(shape_points);
		
				for each(var tri:ITriangle in triangles)
				{
					// BodyDef
					bodyDef = new b2BodyDef();
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
					polyDef.density = 1;
					polyDef.friction = 0.3;
					polyDef.restitution = 0.1;
					
					// Bitmap für Piece erstellen
					//var bmp_ori:BitmapData = new BitmapData(26,26, true, 0x00ffffff);
					//bmp_ori.draw(userData);
					
					// Polygon-Maske erstellen
					var polyMask:Sprite = new Sprite();
					polyMask.graphics.lineStyle(1, 0x000000);
					polyMask.graphics.beginFill(0x0000ff);

						polyMask.graphics.moveTo(shape_points[tri.p3].x * phy_scale + 13, shape_points[tri.p3].y * phy_scale + 13);
						polyMask.graphics.lineTo(shape_points[tri.p2].x * phy_scale + 13, shape_points[tri.p2].y * phy_scale + 13);
						polyMask.graphics.lineTo(shape_points[tri.p1].x * phy_scale + 13, shape_points[tri.p1].y * phy_scale + 13);
						
					polyMask.graphics.endFill();
			
			
					userData.mask = polyMask;
			
	
					var new_bmp:BitmapData = new BitmapData(100,100, true, 0x00ffffff);
					new_bmp.draw(userData);
					

					// Piece erstellen
					//var tmp_thing:BThing = new BThing(parent, 0, new_bmp, 45, bodyDef, polyDef, new b2Vec2(0,0));
					var tmp_thing:BThing = new BThing(parent, 0, new_bmp, 45, bodyDef, polyDef, new b2Vec2(body.GetLinearVelocity().x/1.5, body.GetLinearVelocity().y/1.5));
					
					tmp_thing.add();
				}
			}
		}
		
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
			
			body.CreateShape(boxDef);
			
			var tmp_mass:b2MassData = new b2MassData();
			tmp_mass.mass = 5;
			tmp_mass.I = 3;
			tmp_mass.center.SetZero();
			body.SetMass(tmp_mass);
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
		
		public function BCrate(p:BGame, x:int, y:int)
		{
			parent = p;
			var phy_scale:Number = parent.config.phy_scaling;
			
			bodyDef = new b2BodyDef();
			
			boxDef = new b2PolygonDef();
			boxDef.SetAsBox(13/phy_scale, 13/phy_scale);
			boxDef.density = 1;
			boxDef.friction = 0.7;
			boxDef.restitution = 0.1;
			boxDef.filter.categoryBits = parent.config.categoryBits_bcrate;
			boxDef.filter.maskBits = parent.config.maskBits_bcrate;
			
			bodyDef.position.Set(x/phy_scale, y/phy_scale);
			bodyDef.userData = this;
			
			userData = new object_crate();
			userData.x = x;
			userData.y = y;
			userData.width = 12.5 * 2;
			userData.height = 12.5 * 2;
			userData.smooth = true;
			userData.rotation = 20;
			
			// health
			health_full = 75;
			health = health_full;
		}
		
	}
}













