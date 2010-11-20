#include "Level.h"

Level::Level()
{
	 OleInitialize(0);
 char* f1 = "D:/Babeltech/Projects/Bow/branches/BOW_as/maps/Diamond Mine/level.xml";
 //char* f2 = ".\\sample2.xml";

 XML* x = 0;

 // Load from file or url
 FILE* fp = fopen(f1,"rb");
 if (fp)
	 {
	 // Load from file
	 fclose(fp);
	 x = new XML(f1);
	 }
 else
	 {
	 // Load from url
	 x = new XML(f1,XML_LOAD_MODE_LOCAL_FILE);
	 }

 // Parse status check
 int iPS = x->ParseStatus(); // 0 OK , 1 Header warning (not fatal) , 2 Error in parse (fatal)
 bool iTT = x->IntegrityTest(); // TRUE OK
 if (iPS == 2 || iTT == false)
	 {
	 fprintf(stderr,"Error: XML file %s is corrupt (or not a XML file).\r\n\r\n",f1);
	 delete x;
	 return;
	 }

 // Sample export to stdout
 x->Export(stdout,XML_SAVE_MODE_DEFAULT);

 char y[100] = {0};




 // Sample XML functions
 fprintf(stdout,"\r\n\r\n---------- XML test ----------\r\n");
 XML_VERSION_INFO xI = {0};
 x->Version(&xI);
 fprintf(stdout,"XML version: %u.%u (%s)\r\n",xI.VersionHigh,xI.VersionLow,xI.RDate);
 int m1 = x->MemoryUsage();
 x->CompressMemory();
 int m2 = x->MemoryUsage();
 fprintf(stdout,"Memory used before/after compression: %u / %u bytes.\r\n",m1,m2);
 fprintf(stdout,"XML header: %s\r\n",x->GetHeader()->operator const char *());

	// read all childs / level-elements
	fprintf(stdout,"\r\n\r\n---------- XMLElement test ----------\r\n");
	XMLElement* r = x->GetRootElement();
	int nC = r->GetChildrenNum();
	fprintf(stdout,"Root element has %u children.\r\n",nC);

	// run through all elements
	for(int i = 0 ; i < nC ; i++)
	{
		// do initialisation stuff
		XMLElement* ch = r->GetChildren()[i];
		int nV = ch->GetVariableNum();
		int nP = ch->GetVariableNum();
		int nMaxElName = ch->GetElementName(0);
		char* n = new char[nMaxElName + 1];
		ch->GetElementName(n);

		 //XMLElement* el = ch->FindElementZ("x1");

		 char y[100] = {0};

		r->GetChildren()[i]->FindVariableZ("x1", true)->GetValue(y);


		XMLVariable v = r->GetChildren()[i]->FindVariableZ("x1")[0];

		XMLElement* ch2 = r->GetChildren()[i];
		int nValueLen = ch2->FindVariableZ("TEXT")->GetValue(0, 0);
		char* pValueBuf = new char[nValueLen + 1];
		ch2->FindVariableZ("TEXT")->GetValue(pValueBuf, 0);




		// check for the specific element
		if(strncmp(n,"ground_line",sizeof(n))==0)
		{
			// ground
			fprintf(stdout,"\t Ground %u: Variables: %u , Params: %u , Name: %s\r\n",i,nV,nP,n);
		}
		else
		{
			// anything else
			fprintf(stdout,"\t Child %u: Variables: %u , Name: %s\r\n",i,nV,n);
		}

		// cleanup, always important
		delete[] n;
	}


 /*
 // Add a children to the end
 r->AddElement(new XMLElement(r,(char*)"<testel x=\"1\" />"));

 // Find this element by name
 XMLElement* el = r->FindElementZ("testel");
 if (!el)
	 fprintf(stderr,"Error, element not found!\r\n");
 else
	 {
	 // Add some variables
	 el->AddVariable(new XMLVariable("somename","somevalue"));
	 // Note that the new XMLVariable we added is now owned by el

	 // Export only this element
	 el->Export(stdout,1,XML_SAVE_MODE_ZERO); // this prints <testel somename="somevalue"/>
	 }

 // Find an element that may not exist, get its variable X that may not exist, get 
 // a default value of 0
 int v = r->FindElementZ("elx",true)->FindVariableZ("varx",true)->GetValueInt();
 // Set it to 5, set some more
 r->FindElementZ("elx",true)->FindVariableZ("varx",true)->SetValueInt(5);
 r->FindElementZ("elx",true)->FindVariableZ("varx2",true)->SetValueInt(10);
 // Printout it
 // This would print: <elx varx="5" varx2="10"/>
 r->FindElementZ("elx",true)->Export(stdout,1,XML_SAVE_MODE_ZERO);

 // Remove the var we just added
 int ix = r->FindElement("elx");
 if (ix != -1)
	 r->RemoveVariable(ix);

 // Other XMLElement functions
 r->Copy(); // Copy entire thing to windows clipboard

 XMLElement* nP = XML::Paste();
 if (nP)
	 {
	 fprintf(stdout,"Successfully copy/paste from clipboard.\r\n");
	 delete nP; // This nP is not owned by x, so we must delete it!
	 }

 // Get a duplicate
 XMLElement* dup = r->Duplicate();
 if (dup)
	 delete dup;

 // Add a comment to the root element
 int nComments = r->AddComment(new XMLComment(0,0,"Nice comment"),0); 

 // Add same comment to the header
 x->GetHeader()->AddComment(x->GetRootElement()->GetComments()[nComments - 1]->Duplicate(),0);

 // Use XMLSetString, XMLSetBinaryData
 XMLSetString("El1\\El2\\El3","var1","x",0,x);

 RECT rc = {0};
 GetWindowRect(GetDesktopWindow(),&rc);
 XMLSetBinaryData("El1\\El2\\El3","var2",(char*)&rc,sizeof(rc),0,x);

 // Get again
 RECT rc2 = {0};
 XMLGetBinaryData("El1\\El2\\El3","var2",(char*)&rc2,(char*)&rc2,sizeof(rc2),0,x);
 if (memcmp(&rc,&rc2,sizeof(rc)) != 0)
	 fprintf(stderr,"Error in binary data transfer!\r\n");
 else
	 fprintf(stdout,"Binary data transfer OK!\r\n");

 // Import database in cdrom.mdb
 // Careful; not tested with ACCESS 2007
 /*IMPORTDBPARAMS dbp = {0};
 char f[300] = {0};
 GetCurrentDirectory(300,f);
 strcat(f,"\\cdrom.mdb");
 dbp.dbname = f;
 dbp.nTables = 1;
 dbp.provstr = 0; // use default
 IMPORTDBTABLEDATA tbl = {0};
 strcpy(tbl.name,"Collection"); // Table name in MDB
 strcpy(tbl.itemname,"v");  // Default name for out elements
 tbl.nVariables = 4; // ID , CD , Name , Comments
 char* v1[] = {"ID","CD","Name","Comments"};
 char* v2[] = {"ID","CD","Name","Comments"};
 tbl.Variables = v1;
 tbl.ReplaceVariables = v2; // In case we want different name
 dbp.Tables = &tbl;
 XMLElement* d = 0;
 d = XML::ImportDB(&dbp); 
 if (d && d->IntegrityTest())
	 {
	 d->Export(stdout,1,0);
	 delete d;
	 }
*/

 // XML object save
 // Manipulate export format
 /*XMLEXPORTFORMAT xf = {0};
 xf.UseSpace = true;
 xf.nId = 2;
 x->SetExportFormatting(&xf);
 if (x->Save(f2) == 1)
	fprintf(stdout,"%s saved.\r\n",f2);*/

 // XML object bye bye
 delete x;




 EntityFactory *entityFactory =  new GroundFactory();
	EntityProperties& properties = entityFactory->getDefaultProperties();

 entityFactory = new GroundFactory();
	properties = entityFactory->getDefaultProperties();
	properties.x = 400;
	properties.y = 100;
	properties.width = 1600;
	properties.height = 10;
	entityFactory->create(properties);
	properties.x = -395;
	properties.y = 300;
	properties.width = 10;
	properties.height = 600;
	entityFactory->create(properties);
	properties.x = 1195;
	properties.y = 300;
	properties.width = 10;
	properties.height = 600;
	entityFactory->create(properties);
	properties.x = 400;
	properties.y = 590;
	properties.width = 1600;
	properties.height = 10;
	entityFactory->create(properties);
	properties.x = 400;
	properties.y = 100;
	properties.width = 800;
	properties.height = 10;
	properties.angle = 30;
	entityFactory->create(properties);
}

void Level::initialize()
{

}
