# LiteUI

LiteUI is an abstract user-interface library written in C++.

It has been designed to be a lightweight object-orientated approach for common user-interface elements.


## Features

* Straightforward element hierarchy
* Support for creating interfaces from XML
* Event callbacks
* Virtual methods for high-level control
* Nested groups


## XML

Interfaces can be represented using XML like so:


```
<scene name="Scene 1">
	<group name="Button Group">
		<button width="100" height="100" />
		<button pos_x="150" width="100" height="100" />
	</group>
</scene>
```

This creates a basic button which can be manipulated directly or via the parent group object.

#### TODO

* Object searching by name


#### NOTE

* Every properties has a default value, so naming elements is optional!
