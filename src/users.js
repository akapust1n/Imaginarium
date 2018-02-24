import vars from './vars'
import fetchJsonp from 'fetch-jsonp'

function getNames(users) {
    // let ids = users.map(user => user.viewer_id);
    // axios.get(`https://api.vk.com/method/users.get?access_token=${vars['access_token']}&user_ids=${ids}`).then(
    //     response => {
    //         for (let i = 0; i < users.length; i++) {
    //             users[i].name = response.data.response[i].first_name;
    //         }
    //         return users;
    //     },
    //     error => console.log(error)
    // );
    fetchJsonp(`https://api.vk.com/method/users.get?access_token=${vars['access_token']}&user_ids=${ids}`)
        .then(response => response.json())
        .then(json => {
            console.log('parsed json', json);
            {
                for (let i = 0; i < users.length; i++) {
                    let user = json.response[i];
                    users[i].name = user.first_name + ' ' + user.last_name;
                }
                return users;
            }
        })
        .catch(ex => console.log(ex))
}

export default getNames;