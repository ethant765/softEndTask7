/**
 **** Unit tests for the method Route::operator[]()
 *
 * Route::operator[]() returns the Position at the specified index which
 * represents a certain point on the route.
 *
 * First, we should test if Route::operator[]() behaves correctly when the
 * given index refers to a Position within the Route.
 * To do this, we use a GPX file of a route generated using the GridWorld class
 * and we check that the [] operator returns the correct Position at each
 * index.
 *
 * Route::operator[]() should throw an std::out_of_range exception if the index
 * is out of bounds. We should test that the function throws that exception
 * when given an index which is outside the expected interval (from 0 to the
 * size of the route - 1).
 * We also test that an std::out_of_range exception is thrown when the index
 * is negative.
 * We also test the function for edge cases, for example the first and the last
 * Position of the route which should not throw an exception. In addition, we
 * also test the outer bounds of the array (-1 and the route size).
 *
 * Finally, We test Route::operator[]() using an empty route which does not
 * have any points. Since a route contains an array of Positions, the []
 * operator should throw an std::out_of_range exception at any index.
