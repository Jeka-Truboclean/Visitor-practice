#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class House;
class Factory;
class Bank;

class IVisitor abstract
{
public:
	virtual void VisitHouse(House* home) abstract;
	virtual void VisitFactory(Factory* Factory) abstract;
};

class AbstractBuilding abstract
{
	string Owner;
public:
	virtual void Accept(IVisitor* visitor)abstract;
	string GetOwner()
	{ 
		return Owner;
	}
	void SetOwner(string Owner)
	{
		this->Owner = Owner;
	}
};

class House: public AbstractBuilding
{
	string Material;
	string Variation;
public:
	string GetMaterial()
	{
		return  Material;
	}
	void SetMaterial(string Material)
	{
		this->Material = Material;
	}
	string GetVariation()
	{
		return Variation;
	}
	void SetVariation(string Variation)
	{
		this->Variation = Variation;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitHouse(this);
	}
};

class Factory: public AbstractBuilding
{
	string Size;
	string Type;
public:
	string GetSize()
	{
		return Size;
	}
	void SetSize(string Size)
	{
		this->Size = Size;
	}
	string GetType()
	{
		return Type;
	}
	void SetType(string Type)
	{
		this->Type = Type;
	}
	void Accept(IVisitor* visitor) override
	{
		visitor->VisitFactory(this);
	}
};

// сериализатор в HTML
class HtmlVisitor : public IVisitor
{
public:
	void VisitHouse(House* home) override
	{
		ofstream out("House.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Owner<td><td>" + home->GetOwner() + "</td></tr>";
		result += "<tr><td>Material<td><td>" + home->GetMaterial() + "</td></tr>";
		result += "<tr><td>Variation<td><td>" + home->GetVariation() + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitFactory(Factory* Factory) override
	{
		ofstream out("Factory.html", ios::binary | ios::trunc | ios::out);
		string result = "<html><head></head><body>";
		result += "<table><tr><td>Property<td><td>Value</td></tr>";
		result += "<tr><td>Owner<td><td>" + Factory->GetOwner() + "</td></tr>";
		result += "<tr><td>Type<td><td>" + Factory->GetType() + "</td></tr>";
		result += "<tr><td>Size<td><td>" + Factory->GetSize() + "</td></tr></table>";
		result += "</body></html>";
		out.write(result.c_str(), result.size());
		out.close();
	}
};

// сериализатор в XML
class XmlVisitor: public IVisitor
{
public:
	void VisitHouse(House* home) override
	{
		ofstream out("House.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<House><Owner>" + home->GetOwner() + "</Owner>" +
			"<Material>" + home->GetMaterial() + "</Material>" +
			"<Variation>" + home->GetVariation() + "</Variation></House>";
		out.write(result.c_str(), result.size());
		out.close();
	}
	void VisitFactory(Factory* Factory) override
	{
		ofstream out("Factory.xml", ios::binary | ios::trunc | ios::out);
		string result = "<?xml version='1.0' encoding='UTF-8'?>";
		result += "<Factory><Owner>" + Factory->GetOwner() + "</Owner>" +
			"<Type>" + Factory->GetType() + "</Type>" +
			"<Size>" + Factory->GetSize() + "</Size></Factory>";
		out.write(result.c_str(), result.size());
		out.close();
	}
};

class PC
{
	vector<AbstractBuilding*> devices;
public:
	void Add(AbstractBuilding* b)
	{
		devices.push_back(b);
	}
	void Remove(AbstractBuilding* b)
	{
		auto iter = find(devices.begin(), devices.end(), b);
		if(iter != devices.end())
			devices.erase(iter);
	}
	void Accept(IVisitor* visitor)
	{
		for(AbstractBuilding* b : devices)
			b->Accept(visitor);
	}
};

int main()
{
	PC* building = new PC();
	House* h = new House;
	h->SetOwner("BonaVita");
	h->SetMaterial("Teplosten blocks");
	h->SetVariation("Stalinka");
	building->Add(h);
	Factory* fac = new Factory;
	fac->SetOwner("PrivatBank");
	fac->SetType("Sugar");
	fac->SetSize("11 sqr. km");
	building->Add(fac);

	HtmlVisitor *html = new HtmlVisitor;
	building->Accept(html);
	XmlVisitor *xml = new XmlVisitor;
	building->Accept(xml);
	delete html;
	delete xml;
	delete fac;
	delete h;
	delete building;

	system("pause");
}
