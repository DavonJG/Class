<!DOCTYPE html>
    <html lang="en" dir="ltr">
      <head>
        <meta charset="utf-8">
        <title>GetSmart</title>
        <link rel="stylesheet" href="stylesheet.css">
	<script> src="header.js"</script>
	<script> src="tables.js" src="iCloud Drive/Documents/07 Senior Spring/CIS454 - SoftwareImplementation/Project2/tables.js"</script>
      </head>




<!--- GetSmart header --->
      	<div class="header">
  		<h1>GetSmart</h1>
  		<p>Slogan Placeholder</p>
	</div>



<!--- navbar --->
	<div class="topnav">
  		<a href="Home.html">Home</a>
  		
		<div class="dropdown">
    			<button class="dropbtn">Buy 
      				<i class="fa fa-caret-down"></i>
    			</button>
    			<div class="dropdown-content">
      				<a href="Tutors.html">Tutors</a>
      				<a href="Books.html">Books</a>
     				<a href="Materials.html">Study Materials</a>
    				<a href="Electronics.html">Electronics</a>
    			</div>
  		</div> 
  		
		<a href="Sell.html">Sell</a>
  		<a class="active" href="Activity.html">Activity</a>
  			
		<div class="search-container">
    			<form action="/action_page.php">
      				<input type="text" placeholder="Search.." name="search">
      				<button type="submit">Submit</button>
    			</form>
  		</div>
	</div>




	<input type="text" id="myInput" onkeyup="tableFunction()" placeholder="Search for a recent activity" title="Type in the name of an activity">

	<table id="myTable">
		<tr class="header">
    			<th style="width:20%;">From</th>
    			<th style="width:20%;">To</th>
			<th style="width:20%;">Price</th>
    			<th style="width:60%;">Description</th>
  		</tr>

		<?php
			for($i = 0; $i < 5; $i++){
				$sql = "sql statement";
				echo "<tr>";
				echo "<td> Drew </td>";
				echo "<td> Andrew </td>";
				echo "<td> $99 </td>";
				echo "<td> services ;) </td>";
				echo "</tr>";
			}
		?>


	</table>




            



	<script>
		window.onscroll = function() {headerFunction()};

		var navbar = document.getElementById("navbar");
		var sticky = navbar.offsetTop;

		function headerFunction() {
  		   if (window.pageYOffset >= sticky) {
    		      navbar.classList.add("sticky")
  		   } else {
    		      navbar.classList.remove("sticky");
  		   }
		}
	</script>


        </main>
      </body>
    </html>
