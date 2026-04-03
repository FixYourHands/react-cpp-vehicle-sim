function ListGroup() {
  let items = ["Item 1", "Item 2", "Item 3", "Item 4", "Item 5"];
  //items = [];

  if (items.length === 0) 
    return (
        <>
        <h1>List</h1>
        <p>No items found.</p>
        </>
        );

  return (
    <>
      <h1>List Group</h1>
      <ul className="list-group">
        {items.map((item) => (
          <li className="list-group-item" key = {item} onClick={() => console.log(item)}>{item}</li>
        ))}
      </ul>
    </>
  );
}

export default ListGroup;
