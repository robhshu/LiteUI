# LiteUI

LiteUI is an abstract user-interface library written in C++.

It has been designed to be a lightweight object-orientated approach for common user-interface elements.


## Features

* Straightforward element hierarchy
* Support for creating interfaces from JSON
* Event callbacks
* Virtual methods for control, even at a high-level


## JSON

Interfaces can created using JSON serialization‎ like so:


```
{
	"scene" :	[
	{
		"@name" : "Scene 1",
		"group" : [
		{
			"@name" : "Group 1",
			"button" : [
			{
				"@name" : "Button 1",
				"^pos_x" : 10,
				"^pos_y" : 10,
				"^width" : 100,
				"^height" : 70
			}]
		}]
	}]
}
```

This creates a basic button which can be manipulated directly or via the parent group object.


#### NOTE

* Every properties has a default value, so naming elements is optional!
